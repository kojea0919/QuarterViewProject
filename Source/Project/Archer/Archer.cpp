// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project/Archer/Animation/ArcherAnimInstance.h"
#include "Project/Archer/ArcherPlayerController.h"
#include "Project/Archer/Bow/Bow.h"
#include "Project/Archer/Effect/ArcherMoveSkillFootDecal.h"
#include "Project/Archer/Effect/MoveSkillFootDirt.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcher::AArcher()
	: IsCanRotate(true), ArcherController(nullptr), ArcherAnim(nullptr),Bow(nullptr), LeftFootDecal(nullptr),RightFootDecal(nullptr),FootDirtEffect(nullptr),
	DefaultArmLength(800.0f), DefaultSpeed(600.0f), Attacking(false), CurrentCombo(0), MaxCombo(2), ComboInput(false), CanNextCombo(false),
	MoveAble(true), MoveSkillOn(false), IsUseSkill(false), LookMouseDirection(false), RotateSpeed(120.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Create
	//---------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	QuarterViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("QUARTERVIEWCAMERA"));

	AttackRotationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ATTACKROTATIONTIMELINE"));
	//---------------------------------------------

	//Curve Setting
	//---------------------------------------------
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Player/Archer/CF_ArcherAttackRotate.CF_ArcherAttackRotate"));

	if (Curve.Succeeded())
	{
		RotationCurve = Curve.Object;
	}
	//---------------------------------------------

	//Components Init
	//---------------------------------------------
	SpringArm->SetupAttachment(GetCapsuleComponent());
	QuarterViewCamera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = DefaultArmLength;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, -45.0f, 0.0f));
	SpringArm->SetUsingAbsoluteRotation(true);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ARCHER(TEXT("/Game/Player/Archer/Mesh/Player.Player"));
	if (SK_ARCHER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ARCHER.Object);
	}

	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	//---------------------------------------------

	//Camera Setting
	//---------------------------------------------
	bUseControllerRotationYaw = false;
	SpringArm->bInheritYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	GetCharacterMovement()->MaxAcceleration = 20000.0f;
	GetCharacterMovement()->RotationRate.Yaw= 720;
	//---------------------------------------------

	//Animation Setting
	//---------------------------------------------
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ARCHER_ANIM(TEXT("/Game/Player/Archer/Animation/ABP_Archer.ABP_Archer_C"));
	if (ARCHER_ANIM.Succeeded())
		GetMesh()->SetAnimInstanceClass(ARCHER_ANIM.Class);
	//---------------------------------------------
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
	RotateTimelineFinished.BindUFunction(this, FName("TimelineFinishedFunction"));
	RotateTimelineProgress.BindUFunction(this, FName("UpdateRotation"));
	AttackRotationTimeline->SetTimelineFinishedFunc(RotateTimelineFinished);
	AttackRotationTimeline->AddInterpFloat(RotationCurve, RotateTimelineProgress);
	//----------------------------------------------
}

void AArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//LookMouseDirection이 켜져있으면 마우스 방향으로 회전
	if(LookMouseDirection)
		AddRotateMouseDirection(DeltaTime);
}

void AArcher::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UArcherAnimInstance* Anim = Cast<UArcherAnimInstance>(GetMesh()->GetAnimInstance());
	if (Anim)
		ArcherAnim = Anim;

	InitMaterial();
}

void AArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("BasicAttack"), EInputEvent::IE_Pressed, this, &AArcher::BasicAttackAction);
	PlayerInputComponent->BindAction(TEXT("MoveSkill"), EInputEvent::IE_Pressed, this, &AArcher::MoveSkillAction);
}

void AArcher::PossessedBy(AController* PossessedController)
{
	Super::PossessedBy(PossessedController);

	AArcherPlayerController* NewController = Cast<AArcherPlayerController>(PossessedController);
	if (NewController)
		ArcherController = NewController;
}

void AArcher::SetMoveAble(bool Enable)
{
	MoveAble = Enable;

	if (Enable)
		GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AArcher::BasicAttackAction()
{
	//이동 스킬 중에는 공격 불가능
	if (MoveSkillOn)
		return;

	//현재 공격 중인 상태이고 다음 콤보가 가능한 상태이면 
	//ComboInput을 true로 바꾸고 return
	if (Attacking)
	{
		if (CanNextCombo)
		{
			ComboInput = true;

			UpdateAttackTargetLocation();
			AttackRotationTimeline->PlayFromStart();
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
	UpdateAttackTargetLocation();
	AttackRotationTimeline->PlayFromStart();

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

void AArcher::BasicAttackShoot()
{	
	if (Bow)
		Bow->BasicAttack();

	//기본공격에 화살을 발사하는 동안은 회전을 안하도록 막기
	IsCanRotate = false;
}

void AArcher::MoveSkillAction()
{
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
	//왼쪽, 오른쪽 발 위치 바닥에 Decal 생성
		//--------------------------------
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//왼쪽 발 위치 바닥 좌표 찾기
	//-------------------------------------------------
	FVector FootLocation = GetMesh()->GetBoneLocation(TEXT("Foot_R"));
	FHitResult HitResult;
	FVector Target = FootLocation - FVector(0.0f, 0.0f, 80.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, FootLocation, Target, ECC_Visibility);
	//-------------------------------------------------

	LeftFootDecal = EffectObjPool->GetArcherMoveSkillFootDecal();

	//왼쪽 발 바닥 위치에 생성
	LeftFootDecal->SetActorLocation(HitResult.Location);
	LeftFootDecal->SetActorRotation(GetActorRotation());

	//--------------------------------


	//바닥 마찰로 인한 먼지 효과 생성
	//-----------------------------------------------
	AMoveSkillFootDirt * DirtEffect = EffectObjPool->GetMoveSkillFootDirt();

	DirtEffect->SpawnAndAttachNiagaraEffect(GetMesh(), FName(TEXT("MoveSkillDirtSocket")));
	//DirtEffect->SpwanNiagaraEffect(GetMesh()->GetSocketTransform(FName(TEXT("MoveSkillDirtSocket"))));
	
	//DirtEffect->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// , FName("MoveSkillDirtSocket"));

	UE_LOG(LogTemp, Warning, TEXT("Dirt : %s"), *(DirtEffect->GetActorLocation().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *GetActorLocation().ToString());
	//-----------------------------------------------
}

void AArcher::RotateMouseDirection()
{
	if (nullptr == ArcherController)
		return;

	FVector TargetLocation = ArcherController->GetMouseWorldLocation();
	RotateTargetLocation(TargetLocation - GetActorLocation());
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
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_TorsoHead.M_TBSO_TorsoHead"));
	UMaterialInstanceDynamic * DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(0, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Arms.M_TBSO_Arms"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(1, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Pants.M_TBSO_Pants"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(2, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_LENS_01.M_TBSO_LENS_01"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(3, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Acc.M_TBSO_Acc"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(4, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Boots.M_TBSO_Boots"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(5, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Weapons.M_TBSO_Weapons"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(6, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_TorsoInner.M_TBSO_TorsoInner"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(7, DynMaterial);
	DynMaterialArr.Push(DynMaterial);

	Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Archer/Mesh/Material/M_TBSO_Grenade.M_TBSO_Grenade"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, GetMesh());
	GetMesh()->SetMaterial(8, DynMaterial);
	DynMaterialArr.Push(DynMaterial);
	//---------------------------------------------
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

void AArcher::TimelineFinishedFunction()
{
	
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

