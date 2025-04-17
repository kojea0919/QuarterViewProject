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

	//LookMouseDirection�� ���������� ���콺 �������� ȸ��
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
	//�̵� ��ų �߿��� ���� �Ұ���
	if (MoveSkillOn)
		return;

	//���� ���� ���� �����̰� ���� �޺��� ������ �����̸� 
	//ComboInput�� true�� �ٲٰ� return
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

	//�⺻���� Montage ����
	if (nullptr != ArcherAnim)
		ArcherAnim->PlayBasicAttackMontage();
	

	Attacking = true;
	MoveAble = false;

	//�̵� ���߱�
	//--------------------------------
	if (nullptr == ArcherController)
		return;
	ArcherController->StopMovement();
	//--------------------------------


	//ĳ������ �ε巯�� ȸ���� ���ؼ� ���� �÷��̾��� Rotation��
	//���� ���������� Rotation�� ������ Timeline ����
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

	//���� Ű�� �� �������� �̵� ���� ���·� �����
	//���� ��Ÿ�� ���� �� Idle���·� ���ư���
	if (!ComboInput)
	{
		MoveAble = true;
		ArcherAnim->StopBasicAttackMontage();

		return;
	}
	//���� Ű�� �������� ���� ���� Montage ���
	if (nullptr != ArcherAnim)
	{
		//���� �޺� �ִϸ��̼� ���
		//-------------------------------------------------
		CurrentCombo = (CurrentCombo + 1) % (MaxCombo);

		ArcherAnim->PlayBasicAttackMontageSection(CurrentCombo);
		//-------------------------------------------------

		//���콺 �������� ȸ��
		RotateTargetLocation(AttackTargetLocation - GetActorLocation());

		ComboInput = false;
		CanNextCombo = false;
	}
}

void AArcher::BasicAttackShoot()
{	
	if (Bow)
		Bow->BasicAttack();

	//�⺻���ݿ� ȭ���� �߻��ϴ� ������ ȸ���� ���ϵ��� ����
	IsCanRotate = false;
}

void AArcher::MoveSkillAction()
{
	if (!MoveSkillOn)
	{
		MoveSkillOn = true;
		SetMoveAble(true);

		//���� �������� Montage Cancel
		ArcherAnim->Montage_Stop(0.0f);
		ArcherAnim->PlayMoveSkillMontage();

		//���콺�� ����Ű�� ��ǥ�� �̵� �������� Setting
		//------------------------------------------
		FVector MouseWorldLocation = ArcherController->GetMouseWorldLocation();
		FVector MoveDir = MouseWorldLocation - GetActorLocation();
		MoveDir.Z = 0.0f;
		MoveDir.Normalize();

		RotateTargetLocation(MoveDir);
		//------------------------------------------

		//������ �̵��� ���߱�
		ArcherController->StopMovement();
	}
}

void AArcher::SpawnMoveSkillFootDecal()
{
	//����, ������ �� ��ġ �ٴڿ� Decal ����
		//--------------------------------
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//���� �� ��ġ �ٴ� ��ǥ ã��
	//-------------------------------------------------
	FVector FootLocation = GetMesh()->GetBoneLocation(TEXT("Foot_R"));
	FHitResult HitResult;
	FVector Target = FootLocation - FVector(0.0f, 0.0f, 80.0f);

	GetWorld()->LineTraceSingleByChannel(HitResult, FootLocation, Target, ECC_Visibility);
	//-------------------------------------------------

	LeftFootDecal = EffectObjPool->GetArcherMoveSkillFootDecal();

	//���� �� �ٴ� ��ġ�� ����
	LeftFootDecal->SetActorLocation(HitResult.Location);
	LeftFootDecal->SetActorRotation(GetActorRotation());

	//--------------------------------


	//�ٴ� ������ ���� ���� ȿ�� ����
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

	//�÷��̾��� Rotation�� ���� Rotation
	//�÷��̾� -> ���콺 ������ Rotation�� Ÿ�� Rotation���� Setting
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

	//�÷��̾� -> ���콺 ���� ���� ����ȭ
	//--------------------------------------
	FVector TargetVector = ArcherController->GetMouseWorldLocation() - GetActorLocation();
	TargetVector.Z = 0.0f;
	TargetVector.Normalize();
	//--------------------------------------

	//�÷��̾��� ForwardVector�� TargetVector�� ���̰�
	//�������� ���̸� ȸ���� ���Ѵ�.
	//--------------------------------------
	FVector ForwardVector = GetActorForwardVector();
	if ((TargetVector - ForwardVector).Size() < 0.1f)
		return;
	//--------------------------------------

	//������ �̿��ؼ� TargetVector�� �������� ���������� �Ǵ��Ͽ�
	//�ش� �������� �÷��̾ ȸ����Ų��.
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
	//ȸ���� �Ұ����� ���¸� ȸ���� ���ϵ���
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

