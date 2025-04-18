// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherAnimInstance.h"
#include "Project/Archer/Archer.h"
#include "Project/SkillBase/BaseSkill.h"

UArcherAnimInstance::UArcherAnimInstance()
	: CurrentSpeed(0.0f), Archer(nullptr), CurSkill(nullptr)
{
	InitMontage();
}

void UArcherAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CurrentSpeed Setting
	//-------------------------------
	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentSpeed = Pawn->GetVelocity().Size();
	}

	//-------------------------------
}

void UArcherAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AArcher* PawnOwner = Cast<AArcher>(TryGetPawnOwner());
	if (nullptr != PawnOwner)
		Archer = PawnOwner;
}

void UArcherAnimInstance::PlayBasicAttackMontage()
{
	//AttackMontage가 실행 중이 아닐 때만 실행
	if (!Montage_IsPlaying(BasicAttackMontage))
	{
		Montage_Play(BasicAttackMontage, 0.8f);

		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UArcherAnimInstance::BasicAttackMontageEnd);
		Montage_SetEndDelegate(EndDelegate, BasicAttackMontage);

	}
}

void UArcherAnimInstance::StopBasicAttackMontage()
{
	if (Montage_IsPlaying(BasicAttackMontage))
		Montage_Stop(0.2f, BasicAttackMontage);
}

void UArcherAnimInstance::PlayBasicAttackMontageSection(int32 NewSection)
{	
	//NewSection값이 제대로 넘어왔는지 확인
	//----------------------------------------------
	if (!FMath::IsWithinInclusive(NewSection, 0, 2))
		return;
	//----------------------------------------------

	//다음 Montage 실행
	//----------------------------------------------
	FName SectionName = *FString::Printf(TEXT("Attack%d"), NewSection + 1);
	Montage_JumpToSection(SectionName);
	//----------------------------------------------
}

void UArcherAnimInstance::PlayMoveSkillMontage()
{
	if (!Montage_IsPlaying(MoveSkillMontage))
		Montage_Play(MoveSkillMontage, 1.4f);
}

void UArcherAnimInstance::PlayComboSkillMontageSection(int32 NewSection)
{	
	//다음 Montage 실행
	//----------------------------------------------
	FName SecitonName = *FString::Printf(TEXT("Attack%d"), NewSection);
	Montage_JumpToSection(SecitonName);
	//----------------------------------------------
}

void UArcherAnimInstance::BindSkillMontageEndDelegate(UAnimMontage* SkillMontage)
{
	if (SkillMontage->IsValidLowLevel())
	{
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &UArcherAnimInstance::SkillMontageEnd);

		Montage_SetEndDelegate(EndDelegate, SkillMontage);
	}
}

void UArcherAnimInstance::PlayDesperadoMontage()
{
	if (!Montage_IsPlaying(DesperadoMontage))
	{
		Montage_Play(DesperadoMontage, 1.0f);
	}
}

void UArcherAnimInstance::StopDesperadoMontage()
{
	if (Montage_IsPlaying(DesperadoMontage))
		Montage_Stop(0.2f, DesperadoMontage);
}

void UArcherAnimInstance::AnimNotify_BasicAttackComboCheck()
{
	if (Archer)
	{
		Archer->BasicAttackComboCheck();
		Archer->SetCanNextCombo(false);
	}
}

void UArcherAnimInstance::AnimNotify_BasicAttackInputCheckStart()
{
	if (Archer)
		Archer->SetCanNextCombo(true);
}

void UArcherAnimInstance::AnimNotify_BasicAttackShoot()
{
	if (Archer)
		Archer->BasicAttackShoot();
}

void UArcherAnimInstance::AnimNotify_MoveSkillFootDecalSpawn()
{
	if (Archer)
		Archer->SpawnMoveSkillFootDecal();
}

void UArcherAnimInstance::AnimNotify_RemoveMoveSkillFootDirt()
{
	if (Archer)
		Archer->RemoveMoveSkillFootDirt();
}

void UArcherAnimInstance::Animnotify_CreateMoveSkillFootDirt()
{
	if (Archer)
		Archer->CreateMoveSkillFootDirt();
}

void UArcherAnimInstance::SkillMontageEnd(UAnimMontage*, bool)
{
	//애니메이션이 끝나면 Skill의 End함수를 호출하고
	//CurSkill은 다시 nullptr로 바꿔준다.
	if (CurSkill)
	{
		CurSkill->End();
		CurSkill = nullptr;
	}

	//애니메이션이 끝난걸 Player에게 알려서 스킬 사용중이 아님으로 변수를 setting
	if (Archer)
		Archer->SetUseSkill(false);
}

void UArcherAnimInstance::AnimNotify_PlayerMovable()
{
	if (Archer)
		Archer->SetMoveAble(true);
}

void UArcherAnimInstance::BasicAttackMontageEnd(UAnimMontage*, bool)
{
	if (Archer)
		Archer->BasicAttackMontageEnded();
}

void UArcherAnimInstance::InitMontage()
{
	//Attck Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BASICATTACK_MONTAGE(TEXT("/Game/Player/Archer/Animation/BasicAttackMontage.BasicAttackMontage"));
	if (BASICATTACK_MONTAGE.Succeeded())
		BasicAttackMontage = BASICATTACK_MONTAGE.Object;
	//-------------------------------------------

	//MoveSkill Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MOVESKILL_MONTAGE(TEXT("/Game/Player/Archer/Animation/MoveSkillMontage.MoveSkillMontage"));
	if (MOVESKILL_MONTAGE.Succeeded())
		MoveSkillMontage = MOVESKILL_MONTAGE.Object;
	//-------------------------------------------

	//Desperado Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DESPERADO_MONTAGE(TEXT("/Game/Player/Archer/Animation/Desperado.Desperado"));
	if (DESPERADO_MONTAGE.Succeeded())
		DesperadoMontage = DESPERADO_MONTAGE.Object;
	//-------------------------------------------
}
