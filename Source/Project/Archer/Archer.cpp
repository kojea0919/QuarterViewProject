// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Particles/ParticleSystemComponent.h"	
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Archer/Animation/ArcherAnimInstance.h"
#include "Archer/ArcherPlayerController.h"
#include "Archer/Bow/Bow.h"
#include "Archer/Effect/ArcherMoveSkillFootDecal.h"
#include "Archer/Effect/MoveSkillFootDirt.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Archer/Skill/SkillManagerComponent.h"
#include "Archer/Effect/AfterimageEffect.h"
#include "Archer/Effect/ArcherLaserEffect.h"
#include "Archer/Inventory/InventoryComponent.h"
#include "Archer/Inventory/EquipmentComponent.h"
#include "UI/Inventory.h"
#include "UI/ArcherInteractionUI.h"
#include "UI/DamageText.h"
#include "Item/BaseItem.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "UI/Equipment.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DamageType/ArcherDamageType.h"
#include "DamageType/ArcherBasicDamageType.h"
#include "DamageType/BossDamageType.h"
#include "Engine/DamageEvents.h"
#include "GamePlayEffect/SceneShatter/SceneShatter.h"
#include "GamePlayEffect/SceneShatter/SceneShatterFieldSystemActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "GamePlayEffect/HideMap/HideMapComponent.h"

AArcher::AArcher()
	: IsCanRotate(true), ArcherController(nullptr), ArcherAnim(nullptr), Bow(nullptr), FootDirtEffect(nullptr),
	DefaultSpeed(600.0f), Attacking(false), CurrentCombo(0), MaxCombo(2), ComboInput(false), CanNextCombo(false),
	MoveAble(true), MoveSkillOn(false), IsUseSkill(false), LookMouseDirection(false), RotateSpeed(120.0f), IsCameraZoomOut(false),
	PlayerState(EPlayerState::Normal), RotateToBoss(false), RotationDirectionToBoss(1), IsUpdateCameraTransform(false),
	CameraTransformSpeed(0.1f), CurCameraTransformAlpha(0), CurHP(2000), MaxHP(2000), Dead(true), TargetHideActor(nullptr), IsLineTraceMapComponent(true),
	UltimateSequencePlayer(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Create
	//---------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	QuarterViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("QUARTERVIEWCAMERA"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SCENECAPTURE"));

	SkillRangeMarkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SKILLRANGEMARK"));

	SkillManager = CreateDefaultSubobject<USkillManagerComponent>(TEXT("SKILLMANAGER"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("INVENTORY"));
	Equip = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EQUIP"));

	AttackRotationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ATTACKROTATIONTIMELINE"));
	JumpLocationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("JUMPLOCATIONTIMELINE"));
	CameraShakeJumpLocationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CAMERASHAKEJUMPLOCATIONTIMELINE"));

	InteractionUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTION"));
	//---------------------------------------------

	//Input Setting
	//---------------------------------------------
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>INPUTMAPPINGCONTEXT(TEXT("/Game/GamePlay/Player/Input/IMC_Player.IMC_Player"));
	if (INPUTMAPPINGCONTEXT.Succeeded())
		InputMappingContext = INPUTMAPPINGCONTEXT.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVESKILL_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_MoveSkill.IA_MoveSkill"));
	if (IA_MOVESKILL_INPUTACTION.Succeeded())
		MoveSkillInputAction = IA_MOVESKILL_INPUTACTION.Object;
	//---------------------------------------------

	//Curve Setting
	//---------------------------------------------
	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_ROTATION(TEXT("/Game/GamePlay/Player/Archer/CF_ArcherAttackRotate.CF_ArcherAttackRotate"));

	if (C_ROTATION.Succeeded())
	{
		RotationCurve = C_ROTATION.Object;
	}
	//---------------------------------------------

	//Components Init
	//---------------------------------------------
	SpringArm->SetupAttachment(GetCapsuleComponent());
	QuarterViewCamera->SetupAttachment(SpringArm);
	SceneCapture->SetupAttachment(QuarterViewCamera);
	SceneCapture->bCaptureEveryFrame = false;
	SceneCapture->bCaptureOnMovement = false;

	SpringArm->TargetArmLength = DefaultArmLength;
	SpringArm->SetRelativeRotation(DefaultCameraRotation);
	SpringArm->SetUsingAbsoluteRotation(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ARCHER(TEXT("/Game/GamePlay/Player/Archer/Mesh/Player.Player"));
	if (SK_ARCHER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ARCHER.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SKILLRANGE(TEXT("/Game/GamePlay/Player/Archer/RangeMark/Shape_Plane.Shape_Plane"));
	if (SM_SKILLRANGE.Succeeded())
	{
		SkillRangeMarkMesh->SetStaticMesh(SM_SKILLRANGE.Object);
	}
	SkillRangeMarkMesh->SetupAttachment(RootComponent);
	SkillRangeMarkMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -89.7f));
	SkillRangeMarkMesh->SetHiddenInGame(true);
	SkillRangeMarkMesh->SetRelativeScale3D(FVector(RangeMarkMeshScale, RangeMarkMeshScale, 1.0f));
	SkillRangeMarkMesh->SetCollisionProfileName(TEXT("NoCollision"));

	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UArcherInteractionUI> INTERACTIONUI(TEXT("/Game/GamePlay/Player/UI/UI_ArcherInteraction.UI_ArcherInteraction_C"));
	if (INTERACTIONUI.Succeeded())
	{
		InteractionUI->SetWidgetClass(INTERACTIONUI.Class);
	}
	InteractionUI->SetupAttachment(GetMesh());
	InteractionUI->SetHiddenInGame(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	//---------------------------------------------

	//Camera Setting
	//---------------------------------------------
	bUseControllerRotationYaw = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	GetCharacterMovement()->MaxAcceleration = 20000.0f;
	GetCharacterMovement()->RotationRate.Yaw= 720;

	QuarterViewCamera->SetConstraintAspectRatio(true);
	//---------------------------------------------

	//Animation Setting
	//---------------------------------------------
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ARCHER_ANIM(TEXT("/Game/GamePlay/Player/Archer/Animation/ABP_Archer.ABP_Archer_C"));
	if (ARCHER_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ARCHER_ANIM.Class);
	//---------------------------------------------


	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PLAYERHUD_C(TEXT("/Game/GamePlay/GamePlayEffect/SceneShatter/UI_SceneShatterHUD.UI_SceneShatterHUD_C"));
	if (UI_PLAYERHUD_C.Succeeded())
		SceneShatterWidgetClass = UI_PLAYERHUD_C.Class;

}

void AArcher::BeginPlay()
{
	Super::BeginPlay();

	//Bow Setting
	//----------------------------------------------
	Bow = GetWorld()->SpawnActor<ABow>();
	if (nullptr!=Bow)
	{
		FName BowSocket(TEXT("GripBow"));

		Bow->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, BowSocket); 
		Bow->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		Bow->SetOwner(this);
	}
	//----------------------------------------------

	//TimeLine Setting
	//----------------------------------------------
	RotateTimelineProgress.BindUFunction(this, FName("UpdateRotation"));
	AttackRotationTimeline->AddInterpFloat(RotationCurve, RotateTimelineProgress);

	JumpLocatoinTimelineProgress.BindUFunction(this, FName("UpdateJumpLocation"));
	JumpLocationTimeline->AddInterpVector(JumpCurve, JumpLocatoinTimelineProgress);
	
	CameraShakeJumpLocatoinTimelineProgress.BindUFunction(this, FName("UpdateJumpLocation"));
	CameraShakeJumpLocationTimeline->AddInterpVector(CameraShakeJumpCurve, CameraShakeJumpLocatoinTimelineProgress);
	//----------------------------------------------
	
	AArcherPlayerController* PlayerController = GetController<AArcherPlayerController>();
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}

		//Inventory Setting
		//---------------------------------------------
		if (Inventory)
			Inventory->SetInventory(PlayerController->GetInventory());
		//---------------------------------------------

		//Equipment Setting
		//---------------------------------------------
		if (Equip)
			Equip->SetEquip(PlayerController->GetEquipment());
		//---------------------------------------------
	}
}

void AArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LookMouseDirection이 켜져있으면 마우스 방향으로 회전
	if(LookMouseDirection)
		AddRotateMouseDirection(DeltaTime);

	if (IsCameraZoomOut)
		UpdateZoomOutEffect(DeltaTime);

	if(IsUpdateCameraTransform)
		UpdateCameraTransform(DeltaTime);

	if (IsLineTraceMapComponent)
		HideBlockMapComponent();
}

void AArcher::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UArcherAnimInstance* Anim = Cast<UArcherAnimInstance>(GetMesh()->GetAnimInstance());
	if (Anim)
		ArcherAnim = Anim;

	InitMaterial();
	InitEffect();
}

void AArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveSkillInputAction, ETriggerEvent::Triggered, this, &AArcher::MoveSkillAction);
	}


	PlayerInputComponent->BindAction(TEXT("BasicAttack"), EInputEvent::IE_Pressed, this, &AArcher::BasicAttackAction);
	//PlayerInputComponent->BindAction(TEXT("MoveSkill"), EInputEvent::IE_Pressed, this, &AArcher::MoveSkillAction);
}

void AArcher::PossessedBy(AController* PossessedController)
{
	Super::PossessedBy(PossessedController);

	AArcherPlayerController* NewController = Cast<AArcherPlayerController>(PossessedController);
	if (NewController)
	{
		ArcherController = NewController;
	}
}

float AArcher::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (PlayerState == EPlayerState::UsingUltimate)
		return 0.0f;

	if (nullptr != ArcherAnim)
	{
		//Damage Type에 따라 경직모션 or 넉백모션
		UBossDamageType* DamageType = nullptr;
		if (DamageEvent.DamageTypeClass)
		{
			DamageType = DamageEvent.DamageTypeClass->GetDefaultObject<UBossDamageType>();
		}

		if (nullptr == DamageType)
			return 0;

		switch (DamageType->GetDamageType())
		{
		case EBossDamageType::Stiff:
			PlayerState = EPlayerState::Stiff;
			ArcherAnim->PlaySitffHitMontage();			
			break;
		case EBossDamageType::KnockBack:
			PlayerState = EPlayerState::Down;
			ArcherAnim->PlayKnockBackMontage();
			ComputeRotateDirectionToBoss();
			//RotateToBoss = true;
			break;
		case EBossDamageType::CameraShake:
			PlayerState = EPlayerState::Down;
			ArcherAnim->PlayKnockBackMontage();
			ComputeRotateDirectionToBoss();
			if(ArcherController)
			{
				ArcherController->ClientStartCameraShake(ArcherJumpCameraShakeClass);
			}
			break;
		}

		CurHP -= Damage;

		DamageProc(Damage);
		if (ArcherController)
		{
			ArcherController->SetPlayerCurrentHPRate(CurHP / MaxHP);
		}

		if (CurHP <= 0)
		{
			if (DamageType->GetDamageType() == EBossDamageType::Stiff)
				ArcherAnim->PlaySitffDeadMontage();
			else
				ArcherAnim->PlayKnockBackDeadMontage();

			Dead = true;

			if (ArcherController)
			{
				ArcherController->PlayerDead();	
				ArcherController->StopMovement();
			}
		}

	}

	return 0.0f;
}

void AArcher::SetMoveAble(bool Enable)
{
	MoveAble = Enable;

	if (Enable)
		GetCharacterMovement()->bOrientRotationToMovement = true;
	else
		GetController()->StopMovement();
}

void AArcher::SetBowChargingEffect(bool Enable)
{
	if (Bow)
		Bow->SetChargingEffect(Enable);
}

void AArcher::RangeMarkOn(float Range)
{
	SkillRangeMarkMesh->SetWorldScale3D(FVector(Range *RangeMarkMeshScale * 2, Range * RangeMarkMeshScale * 2,1.0f));
	SkillRangeMarkMesh->SetHiddenInGame(false);
}

void AArcher::RangeMarkOff()
{
	SkillRangeMarkMesh->SetHiddenInGame(true);
}

void AArcher::SetAttackAreaMark(bool Enable)
{
	if (ArcherController)
		ArcherController->SetAreaMarkEffectVisible(Enable);
}

void AArcher::AddItem(UBaseItem* Item)
{
	if (Inventory)
		Inventory->AddItem(Item);
}

bool AArcher::IsCanAddItem()
{
	if (Inventory)
		return Inventory->IsCanAddItem();
	return false;
}

void AArcher::UnEquipHat()
{
	if (Equip)
		Equip->UnEquipHat();
}

void AArcher::UnEquipChest()
{
	if (Equip)
		Equip->UnEquipChest();
}

void AArcher::UnEquipPants()
{
	if (Equip)
		Equip->UnEquipPants();
}

void AArcher::UnEquipGlove()
{
	if (Equip)
		Equip->UnEquipGlove();
}

void AArcher::UnEquipWeapon()
{
	if (Equip)
		Equip->UnEquipWeapon();
}

const UBaseItem* AArcher::GetWeaponItem() const
{
	if (Equip)
		return Equip->GetWeapon();
	return nullptr;
}

const UBaseItem* AArcher::GetArmorItem(EArmorType ArmorType) const
{
	if (Equip)
		return Equip->GetArmor(ArmorType);
	return nullptr;
}

void AArcher::SetVisibleInteractionUI(bool Enable)
{
	if (InteractionUI)
	{
		if (Enable)
		{
			InteractionUI->SetHiddenInGame(!Enable);
			InteractionUI->SetVisibility(true);
			UArcherInteractionUI * UI = Cast<UArcherInteractionUI>(InteractionUI->GetWidget());
			if (UI)
				UI->PlayScaleUpAnimation();

		}
		else
		{
			InteractionUI->SetHiddenInGame(Enable);
			InteractionUI->SetVisibility(false);
			UArcherInteractionUI* UI = Cast<UArcherInteractionUI>(InteractionUI->GetWidget());
			if (UI)
				UI->PlayScaleDownAnimation();
		}
	}
}

FTransform AArcher::GetSoulSiphonEffectPos() const
{
	return GetMesh()->GetSocketTransform(TEXT("SoulSiphonLoopPos"));
}

void AArcher::SetPlayingLevelSequenceState()
{
	//궁극기 사용중이면 궁극기 스킵되게 구현
	//---------------------------------------------------------------------
	if (PlayerState == EPlayerState::UsingUltimate && UltimateSequencePlayer)
	{
		if (ArcherAnim)
			ArcherAnim->StopAllMontages(0);
		UltimateSequencePlayer->Stop();
	}
	//---------------------------------------------------------------------

	PlayerState = EPlayerState::PlayingLevelSequence;
	SetActorHiddenInGame(true);
}

void AArcher::SetUpdateCameraTransform(bool Reverse)
{
	IsUpdateCameraTransform = true;
	CurCameraTransformAlpha = 0.f;

	if (Reverse)
	{
		StartCameraRotation = TargetCameraRotation;
		StartCameraLocation = TargetCameraLocation;
		StartArmLength = TargetArmLength;

		TargetCameraRotation = DefaultCameraRotation;
		TargetCameraLocation = FVector(0.0f,0.0f,0.0f);
		TargetArmLength = DefaultArmLength;
	}
	else
	{
		StartCameraRotation = SpringArm->GetRelativeRotation();
		StartCameraLocation = SpringArm->GetRelativeLocation();
		StartArmLength = SpringArm->TargetArmLength;
	}
}

void AArcher::JumpingStart()
{
	IsJumping = true;

	JumpStartPoint = GetActorLocation();

	if (IsCameraShakeJump)
	{
		CameraShakeJumpLocationTimeline->PlayFromStart();

		GetWorld()->GetTimerManager().SetTimer(JumpCameraShakeTimerHandle, this, &AArcher::PlayJumpCameraShake, 0.9f, false);
	}
	else
		JumpLocationTimeline->PlayFromStart();
}

bool AArcher::GetIsVisibleInteractionUI() const
{
	if (InteractionUI)
	{
		return InteractionUI->IsVisible();
	}

	return false;
}


UBaseItem* AArcher::EquipItem(UBaseItem* Item)
{
	if (!Equip)
		return nullptr;

	UBaseItem* PrevItem = nullptr;

	if (Item->GetItemType() == EItemListType::Weapon)
	{
		PrevItem = Equip->EquipWeapon(Cast<UWeaponItem>(Item));
	}
	else if (Item->GetItemType() == EItemListType::Armor)
	{
		PrevItem = Equip->EquipArmor(Cast<UArmorItem>(Item));
	}
	return PrevItem;
}

void AArcher::BasicAttackAction()
{
	if (EPlayerState::Normal != PlayerState)
		return;

	//이동 스킬 중이면 공격 불가능
	if (MoveSkillOn)
		return;

	//현재 공격 중인 상태이고 다음 콤보가 가능한 상태이면 
	//ComboInput을 true로 바꾸고 return
	if (Attacking)
	{
		if (CanNextCombo)
		{
			ComboInput = true;

			RotateMouseDirectionTimeLineVersion();
		}
		return;
	}

	//기본공격 Montage 실행
	if (nullptr != ArcherAnim)
		ArcherAnim->PlayBasicAttackMontage();
	

	Attacking = true;
	MoveAble = false;

	//이동 멈추기
	//--------------------------------
	if (nullptr == ArcherController)
		return;
	ArcherController->StopMovement();
	//--------------------------------


	//캐릭터의 부드러운 회전을 위해서 현재 플레이어의 Rotation과
	//공격 방향으로의 Rotation을 저장후 Timeline 실행
	//--------------------------------
	RotateMouseDirectionTimeLineVersion();
}

void AArcher::BasicAttackMontageEnded()
{
	IsCanRotate = true;

	ComboInput = false;
	MoveAble = true;
	Attacking = false;

	CurrentCombo = 0;
	CanNextCombo = false;
}

void AArcher::BasicAttackComboCheck()
{
	IsCanRotate = true;

	//공격 키가 안 눌렸으면 이동 가능 상태로 만들고
	//공격 몽타주 정지 후 Idle상태로 돌아가기
	if (!ComboInput)
	{
		MoveAble = true;
		ArcherAnim->StopBasicAttackMontage();

		return;
	}
	//공격 키가 눌렸으면 다음 공격 Montage 재생
	if (nullptr != ArcherAnim)
	{
		//다음 콤보 애니메이션 재생
		//-------------------------------------------------
		CurrentCombo = (CurrentCombo + 1) % (MaxCombo);

		ArcherAnim->PlayBasicAttackMontageSection(CurrentCombo);
		//-------------------------------------------------

		//마우스 방향으로 회전
		RotateTargetLocation(AttackTargetLocation - GetActorLocation());

		ComboInput = false;
		CanNextCombo = false;
	}
}

void AArcher::BasicAttackShot()
{	
	if (Bow)
	{
		Bow->BasicAttack();

		TArray<FHitResult> HitResults;
		
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FVector BoxLocation = GetActorLocation() + GetActorForwardVector() * BasicAttackBoxExtent.X + FVector(0.0f, 0.0f, BasicAttackHeightOffset);

		bool IsHit = GetWorld()->SweepMultiByObjectType(HitResults,
			BoxLocation,BoxLocation,
			GetActorQuat(),ObjectQueryParams,
			FCollisionShape::MakeBox(BasicAttackBoxExtent),
			Params);
		
		/*DrawDebugBox(GetWorld(),
			BoxLocation,
			BasicAttackBoxExtent,
			GetActorQuat(),
			FColor::Green,false,2);*/

		//충돌이 된 경우
		if (IsHit)
		{
			for (auto& Hit : HitResults)
			{
				UGameplayStatics::ApplyDamage(
					Hit.GetActor(),
					BasicAttackBaseDamage,
					GetInstigatorController(),
					this,
					UArcherBasicDamageType::StaticClass());
			}
		}
	}

	//기본공격에 화살을 발사하는 동안은 회전을 안하도록 막기
	IsCanRotate = false;
}

void AArcher::MoveSkillAction()
{
	if (EPlayerState::Normal != PlayerState)
		return;

	if (!MoveSkillOn)
	{
		MoveSkillOn = true;
		SetMoveAble(true);

		//현재 동작중인 Montage Cancel
		ArcherAnim->Montage_Stop(0.0f);
		ArcherAnim->PlayMoveSkillMontage();

		//마우스가 가리키는 좌표를 이동 방향으로 Setting
		//------------------------------------------
		FVector MouseWorldLocation = ArcherController->GetMouseWorldLocation();
		FVector MoveDir = MouseWorldLocation - GetActorLocation();
		MoveDir.Z = 0.0f;
		MoveDir.Normalize();

		RotateTargetLocation(MoveDir);
		//------------------------------------------

		//이전에 이동은 멈추기
		ArcherController->StopMovement();
	}
}

void AArcher::SpawnMoveSkillFootDecal()
{
	//오른쪽 발 위치 바닥에 Decal 생성
	//--------------------------------
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//오른쪽 발 위치 바닥 좌표 찾기
	//-------------------------------------------------
	FVector FootLocation = GetMesh()->GetBoneLocation(TEXT("Foot_R"));
	FHitResult HitResult;
	FVector Target = FootLocation - FVector(0.0f, 0.0f, 80.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, FootLocation, Target, ECC_Visibility);
	//-------------------------------------------------

	AArcherMoveSkillFootDecal * RightFootDecal = EffectObjPool->GetArcherMoveSkillFootDecal();

	//오른쪽 발 바닥 위치에 생성
	RightFootDecal->SetActorLocation(HitResult.Location);
	RightFootDecal->SetActorRotation(GetActorRotation());
}

void AArcher::RemoveMoveSkillFootDirt()
{
	if (FootDirtEffect)
	{
		FootDirtEffect->SetEffectEnable(false);
	}
}

void AArcher::CreateMoveSkillFootDirt()
{
	if (FootDirtEffect)
	{
		FootDirtEffect->SetEffectEnable(true);
	}
}

void AArcher::SpecialAttackShot()
{
	if (Bow)
		Bow->SpecialAttack();
}

void AArcher::FlippingShot1()
{
	if (Bow)
		Bow->FlippingShot1();
}

void AArcher::FlippingShot2()
{
	if (Bow)
		Bow->FlippingShot2();
}

void AArcher::FlippingShot3()
{
	if (Bow)
		Bow->FlippingShot3();
}

void AArcher::ArrowShowerShot()
{
	if (Bow)
		Bow->ArrowShowerShot();
}

void AArcher::PulseShot()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	AArcherLaserEffect* LaserEffect = EffectObjPool->GetArcherLaserEffect();

	LaserEffect->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LaserEffectPos"));
}

void AArcher::SpawnPulseShotFootDecal()
{
	//왼쪽, 오른쪽 발 위치 바닥에 Decal 생성
	//--------------------------------
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//오른쪽 발 위치 바닥 좌표 찾기
	//-------------------------------------------------
	FVector FootLocation = GetMesh()->GetBoneLocation(TEXT("Foot_R"));
	FHitResult HitResult;
	FVector Target = FootLocation - FVector(0.0f, 0.0f, 80.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, FootLocation, Target, ECC_Visibility);
	//-------------------------------------------------

	AArcherMoveSkillFootDecal* RightFootDecal = EffectObjPool->GetArcherMoveSkillFootDecal();

	//오른쪽 발 바닥 위치에 생성
	RightFootDecal->SetActorLocation(HitResult.Location + GetActorForwardVector() * 30.0f);
	RightFootDecal->SetActorRotation(GetActorRotation() + FRotator(0.0f,180.0f,0.0f));
	RightFootDecal->SetTargetRate(0.7f);

	//왼 발 위치 바닥 좌표 찾기
	//-------------------------------------------------
	FootLocation = GetMesh()->GetBoneLocation(TEXT("Foot_L"));
	HitResult;
	Target = FootLocation - FVector(0.0f, 0.0f, 80.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, FootLocation, Target, ECC_Visibility);
	//-------------------------------------------------

	AArcherMoveSkillFootDecal* LeftFootDecal = EffectObjPool->GetArcherMoveSkillFootDecal();

	//왼쪽 발 바닥 위치에 생성
	LeftFootDecal->SetActorLocation(HitResult.Location + GetActorForwardVector() * 30.0f);
	LeftFootDecal->SetActorRotation(GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f));
	LeftFootDecal->SetTargetRate(0.7f);
}

void AArcher::CreateAfterimage()
{
	FRotator ActorRotation = GetActorRotation();
	FVector ActorLocation = GetActorLocation();
	//ActorLocation.Z = 0.0f;
	ActorRotation += FRotator(0.0f, -90.0f, 0.0f);

	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	AAfterimageEffect* AfterimageEffect = EffectObjPool->GetAfterimageEffect();

	AfterimageEffect->SetActorLocation(ActorLocation);
	AfterimageEffect->SetActorRotation(ActorRotation);
	AfterimageEffect->SetOpacity(1.0f);

	AfterimageEffect->SetOwner(this);
	AfterimageEffect->CopyAnimationPos(GetMesh());
	AfterimageEffect->SetActorTickEnabled(true);
}

void AArcher::PlayCameraShake()
{
	if (ArcherSkillCameraShakeClass && ArcherController)
		ArcherController->ClientStartCameraShake(ArcherSkillCameraShakeClass);
}

void AArcher::PlayJumpCameraShake()
{
	if (ArcherJumpCameraShakeClass && ArcherController)
	{
		ArcherController->ClientStartCameraShake(ArcherJumpCameraShakeClass);
	}
}

void AArcher::PlayCameraZoomOut(int StartSpringArmLength, float Speed)
{
	IsCameraZoomOut = true;
	ZoomOutSpeed = Speed;
	CurrentSpringArmLength = StartSpringArmLength;

	if (SpringArm)
		SpringArm->TargetArmLength = StartSpringArmLength;
}

void AArcher::CreateSceneShatter()
{
	SceneCapture->CaptureScene();

	SceneShatter = GetWorld()->SpawnActor<ASceneShatter>(SceneShatterClass, FVector(0.0f, 0.0f, -4000.0f), FRotator());
	FieldSystemActor = GetWorld()->SpawnActor<ASceneShatterFieldSystemActor>(FieldSystemActorClass, FVector(79.0f, 0.0f, -4000.0f), FRotator());

	SceneShatterWidget = CreateWidget<UUserWidget>(GetWorld(), SceneShatterWidgetClass);
	SceneShatterWidget->AddToViewport(1);

	GetWorld()->GetTimerManager().SetTimer(ShatterCreateTimerHandle, this, &AArcher::ApplyShatterForce, 0.4f, false);
}

void AArcher::PlayUltimateSequence()
{
	if (UltimateSequence)
	{
		if (nullptr == UltimateSequencePlayer)
		{
			ALevelSequenceActor* SequenceActor;
			UltimateSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), UltimateSequence, FMovieSceneSequencePlaybackSettings(), SequenceActor);
		}

		if (UltimateSequencePlayer)
		{
			UltimateSequencePlayer->OnFinished.AddDynamic(this, &AArcher::UltimateSequenceFinished);
			PlayerState = EPlayerState::UsingUltimate;
			UltimateSequencePlayer->Play();
		}

		if (ArcherController)
		{
			ArcherController->StartedUltimateSequence();
		}
	}
}

void AArcher::UltimateSequenceFinished()
{
	if (ArcherAnim)
		ArcherAnim->ResumeCurrentMontage();
}

void AArcher::RotateMouseDirection()
{
	if (nullptr == ArcherController)
		return;

	FVector TargetLocation = ArcherController->GetMouseWorldLocation();
	RotateTargetLocation(TargetLocation - GetActorLocation());
}

void AArcher::RotateMouseDirectionTimeLineVersion()
{
	UpdateAttackTargetLocation();
	AttackRotationTimeline->PlayFromStart();
}

void AArcher::ResetState()
{
	IsCanRotate = true;
	ComboInput = false;
	MoveAble = true;
	Attacking = false;
	CurrentCombo = 0;
	CanNextCombo = false;
	MoveSkillOn = false;
	IsUseSkill = false;
	LookMouseDirection = false;
	IsCameraZoomOut = false;
	RotateToBoss = false;
	Dead = false;
	CurHP = MaxHP;

	if (ArcherAnim)
		ArcherAnim->PlayRespawnMontage();

	PlayerState = EPlayerState::Normal;

	CustomTimeDilation = 1.f;
}

void AArcher::SetSlowState(bool Enable)
{
	if (Enable)
		CustomTimeDilation = 0.7f;
	else
		CustomTimeDilation = 1.0f;
}

void AArcher::InitPhase3State()
{
	PlayerState = EPlayerState::Normal;

	CustomTimeDilation = 1.f;
}

void AArcher::UltimateEnd()
{
	PlayerState = EPlayerState::Normal;
}

void AArcher::UltimateShot()
{
	if (Bow)
	{
		if (ArcherController)
		{
			Bow->UltimateShot(ArcherController->GetCurrentBoss());

		}
	}
}

void AArcher::RotateBossDirection(float DeltaSecond)
{
	if (nullptr == ArcherController)
		return;

	FVector BossLocation = ArcherController->GetBossLocation();
	FVector PlayerToBossVector = BossLocation - GetActorLocation();
	PlayerToBossVector.Normalize();

	if (PlayerToBossVector.Equals(GetActorForwardVector(), 0.07f))
	{
		RotateToBoss = false;
		return;
	}

	AddActorWorldRotation(FRotator(0.0f, DeltaSecond * KnockBackRotateSpeed * RotationDirectionToBoss, 0.0f));}

void AArcher::ComputeRotateDirectionToBoss()
{
	if (nullptr == ArcherController)
		return;

	FVector BossLocation = ArcherController->GetBossLocation();
	FVector PlayerToBossVector = BossLocation - GetActorLocation();
	PlayerToBossVector.Normalize();


	SetActorRotation(PlayerToBossVector.Rotation());
	return;


	float Z = PlayerToBossVector.Cross(GetActorForwardVector()).Z;
	
	if (Z)
		Z = 1;
	else
		Z = -1;
}

void AArcher::UpdateAttackTargetLocation()
{
	if (nullptr == ArcherController)
		return;

	//플레이어의 Rotation을 시작 Rotation
	//플레이어 -> 마우스 벡터의 Rotation을 타겟 Rotation으로 Setting
	//--------------------------------------------------------------
	StartRotator = GetActorRotation();

	AttackTargetLocation = ArcherController->GetMouseWorldLocation();
	FVector ActorToAttackTarget = AttackTargetLocation - GetActorLocation();

	TargetRotator = (AttackTargetLocation - GetActorLocation()).Rotation();
	TargetRotator.Pitch = 0.f;
	//--------------------------------------------------------------
}

void AArcher::InitMaterial()
{
	//Material Setting
	//---------------------------------------------
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_TorsoHead.M_TBSO_TorsoHead"));
	UMaterialInstanceDynamic * DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(0, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Arms.M_TBSO_Arms"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(1, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Pants.M_TBSO_Pants"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(2, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_LENS_01.M_TBSO_LENS_01"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(3, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Acc.M_TBSO_Acc"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(4, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Boots.M_TBSO_Boots"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(5, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Weapons.M_TBSO_Weapons"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(6, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_TorsoInner.M_TBSO_TorsoInner"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(7, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Mesh/Material/M_TBSO_Grenade.M_TBSO_Grenade"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(8, DynMaterial);
	DynMaterialArr.Push(DynMaterial);
	//---------------------------------------------
}

void AArcher::InitEffect()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//바닥 마찰로 인한 먼지 효과 생성
	FootDirtEffect = EffectObjPool->GetMoveSkillFootDirt();

	FootDirtEffect->SpawnAndAttachNiagaraEffect(GetMesh(), FName(TEXT("MoveSkillDirtSocket")));

	FootDirtEffect->SetEffectEnable(false);
}

void AArcher::AddRotateMouseDirection(float DeltaTime)
{
	if (nullptr == ArcherController)
		return;

	//플레이어 -> 마우스 방향 벡터 정규화
	//--------------------------------------
	FVector TargetVector = ArcherController->GetMouseWorldLocation() - GetActorLocation();
	TargetVector.Z = 0.0f;
	TargetVector.Normalize();
	//--------------------------------------

	//플레이어의 ForwardVector와 TargetVector의 차이가
	//오차범위 안이면 회전을 안한다.
	//--------------------------------------
	FVector ForwardVector = GetActorForwardVector();
	if ((TargetVector - ForwardVector).Size() < 0.1f)
		return;
	//--------------------------------------

	//외적을 이용해서 TargetVector가 왼쪽인지 오른쪽인지 판단하여
	//해당 방향으로 플레이어를 회전시킨다.
	//--------------------------------------
	FVector CrossProduct = FVector::CrossProduct(ForwardVector, TargetVector);
	if (CrossProduct.Z > 0.0f)
		AddActorLocalRotation(FRotator(0.0f, DeltaTime * RotateSpeed, 0.0f));
	else
		AddActorLocalRotation(FRotator(0.0f, -DeltaTime * RotateSpeed, 0.0f));
	//--------------------------------------
}

void AArcher::UpdateZoomOutEffect(float DeltaTime)
{
	CurrentSpringArmLength += DeltaTime * ZoomOutSpeed;

	float NewArmLength = CurrentSpringArmLength;
	if (CurrentSpringArmLength >= DefaultArmLength)
	{
		NewArmLength = DefaultArmLength;
		IsCameraZoomOut = false;
	}

	SpringArm->TargetArmLength = NewArmLength;

}

void AArcher::ApplyShatterForce()
{
	FieldSystemActor->Explode();

	GetWorld()->GetTimerManager().SetTimer(ShatterDestroyTimerHandle, this, &AArcher::DestroyShatterEffect, 2.3f, false);
}

void AArcher::DestroyShatterEffect()
{
	SceneShatter->Destroy();
	FieldSystemActor->Destroy();
	SceneShatterWidget->RemoveFromParent();
}

void AArcher::UpdateCameraTransform(float DeltaTime)
{
	CurCameraTransformAlpha += DeltaTime * CameraTransformSpeed;

	float CurArmLength = FMath::Lerp(StartArmLength, TargetArmLength, CurCameraTransformAlpha);

	FQuat CurQ = StartCameraRotation.Quaternion();
	FQuat TargetQ = TargetCameraRotation.Quaternion();
	FQuat ResultQ = FQuat::Slerp(CurQ, TargetQ, CurCameraTransformAlpha);

	FVector ResultVec = FMath::Lerp(StartCameraLocation, TargetCameraLocation, CurCameraTransformAlpha);

	if (CurCameraTransformAlpha >= 1.0f)
	{
		IsUpdateCameraTransform = false;
		SpringArm->TargetArmLength = TargetArmLength;
		SpringArm->SetRelativeRotation(TargetCameraRotation);
		SpringArm->SetRelativeLocation(TargetCameraLocation);
		return;
	}

	SpringArm->TargetArmLength = CurArmLength;
	SpringArm->SetRelativeRotation(ResultQ.Rotator());
	SpringArm->SetRelativeLocation(ResultVec);
}

void AArcher::DamageProc(float Damage)
{
	UDamageText* DamageText = CreateWidget<UDamageText>(GetWorld(), DamageTextWidgetClass);
	if (DamageText)
	{
		DamageText->AddToViewport();
		DamageText->SetDamageText(Damage);

		//데미지 Text위치 지정
		//------------------------------------
		FVector2D ScreenPos;
		FVector UILocation = GetActorLocation() + DamageTextOffset;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (nullptr == PlayerController)
			return;

		UGameplayStatics::ProjectWorldToScreen(PlayerController, UILocation, ScreenPos);
		DamageText->SetPlayerController(PlayerController);
		DamageText->SetOwnerLocation(UILocation);

		DamageText->SetPositionInViewport(ScreenPos);
		DamageText->PlayBasicDamageTextAnimation();
		DamageText->SetColorAndOpacity(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		//------------------------------------
	}
}

FVector AArcher::GetRandomVector() const
{
	FVector ReturnVector; 
	float Range = RandomVectorRange;
	ReturnVector.X = FMath::RandRange(-Range, Range);
	ReturnVector.Y = FMath::RandRange(-Range, Range);
	ReturnVector.Z = FMath::RandRange(-Range, Range);
	return ReturnVector;
}

void AArcher::HideBlockMapComponent()
{
	FVector Start = QuarterViewCamera->GetComponentLocation();
	FVector End = QuarterViewCamera->GetForwardVector() * SpringArm->TargetArmLength + Start;

	FHitResult HitResult;
	FCollisionQueryParams Params;

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End,
		ECollisionChannel::ECC_GameTraceChannel6, Params))
	{
		if (TargetHideActor == HitResult.GetActor() || TargetHideActor != nullptr)
			return;

		TargetHideActor = Cast<AHideMapComponent>(HitResult.GetActor());
		if (TargetHideActor)
		{
			TargetHideActor->SetOpacityMask(0);
		}
	}
	else
	{
		if (TargetHideActor)
		{
			TargetHideActor->SetOpacityMask(1);

			TargetHideActor = nullptr;
		}
	}

}

void AArcher::UpdateRotation(float Alpha)
{
	//회전이 불가능한 상태면 회전을 안하도록
	//------------------------------------------------
	if (!IsCanRotate)
		return;
	//------------------------------------------------

	FRotator NewRotation = FMath::Lerp(StartRotator, TargetRotator, Alpha);
	SetActorRotation(NewRotation);
}

void AArcher::UpdateJumpLocation(FVector Alpha)
{
	if (Alpha.X > 0.95f)
	{
		IsJumping = false;
	}

	FVector NewLocation = FMath::Lerp(JumpStartPoint, JumpEndPoint, Alpha);
	SetActorLocation(NewLocation);
}

void AArcher::RotateTargetLocation(FVector TargetVector)
{
	TargetVector.Z = 0.0f;
	FRotator NewRotator = FRotationMatrix::MakeFromX(TargetVector).Rotator();
	SetActorRotation(NewRotator);
}

void AArcher::SetMoveSkillEmissiveIntensity(float Intensity)
{
	DynMaterialArr[0]->SetScalarParameterValue(FName("MoveSkill_EmissiveIntensity"), Intensity);
	DynMaterialArr[1]->SetScalarParameterValue(FName("MoveSkill_EmissiveIntensity"), Intensity);
	DynMaterialArr[2]->SetScalarParameterValue(FName("MoveSkill_EmissiveIntensity"), Intensity);
	DynMaterialArr[5]->SetScalarParameterValue(FName("MoveSkill_EmissiveIntensity"), Intensity);
	DynMaterialArr[7]->SetScalarParameterValue(FName("MoveSkill_EmissiveIntensity"), Intensity);
}

