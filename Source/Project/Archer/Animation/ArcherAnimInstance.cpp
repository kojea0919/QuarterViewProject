// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherAnimInstance.h"
#include "Archer/Archer.h"
#include "SkillBase/BaseSkill.h"
#include "SkillBase/ComboSkill/ComboSkill.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Archer/Effect/ArcherDesperadoSkillEffect.h"

UArcherAnimInstance::UArcherAnimInstance()
	: CurrentSpeed(0.0f),IsBound(false),IsJumping(false), Archer(nullptr), CurSkill(nullptr)
{
	InitMontage();
}

void UArcherAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//CurrentSpeed Setting
	//-------------------------------
	if (Archer)
	{
		CurrentSpeed = Archer->GetVelocity().Size();
		IsBound = Archer->GetIsBound();
		IsJumping = Archer->GetIsJumping();
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
	FName SectionName = *FString::Printf(TEXT("Attack%d"), NewSection);
	Montage_JumpToSection(SectionName);
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

void UArcherAnimInstance::PlayKickShotMontage()
{
	if (!Montage_IsPlaying(DesperadoMontage))
	{
		Montage_Play(DesperadoMontage, 1.0f);
	}
}

void UArcherAnimInstance::StopKickShotMontage()
{
	if (Montage_IsPlaying(DesperadoMontage))
		Montage_Stop(0.2f, DesperadoMontage);
}

void UArcherAnimInstance::PlaySitffHitMontage()
{
	if (!Montage_IsPlaying(StiffHitMontage))
	{
		Montage_Play(StiffHitMontage, 1.0f);
	}
}

void UArcherAnimInstance::PlayKnockBackMontage()
{
	if (!Montage_IsPlaying(KnockBackMontage))
	{
		Montage_Play(KnockBackMontage, 1.0f);
	}
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

void UArcherAnimInstance::AnimNotify_BasicAttackShot()
{
	if (Archer)
		Archer->BasicAttackShot();
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

void UArcherAnimInstance::AnimNotify_PlayerUnMovalbe()
{
	if (Archer)
	{
		Archer->SetMoveAble(false);
	}
}

void UArcherAnimInstance::AnimNotify_SpawnDeperadoEffect()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	AArcherDesperadoSkillEffect* Effect= EffectObjPool->GetDesperadoSkillEffect();
	if (Effect)
	{
		Effect->SpawnAndAttachNiagaraEffect(Archer->GetMesh(), FName(TEXT("DesperadoEffectPos")));
	}
}

void UArcherAnimInstance::AnimNotify_SkillComboCheck()
{
	if (CurExcuteComboSkill)
	{
		CurExcuteComboSkill->SkillComboCheck();
		CurExcuteComboSkill->SetCanNextCombo(false);
	}
}

void UArcherAnimInstance::AnimNotify_SkillInputCheckStart()
{
	if (CurExcuteComboSkill)
		CurExcuteComboSkill->SetCanNextCombo(true);
}

void UArcherAnimInstance::AnimNotify_SpecialAttackShot()
{
	if (Archer)
		Archer->SpecialAttackShot();
}

void UArcherAnimInstance::AnimNotify_FlippingShot1()
{
	if (Archer)
		Archer->FlippingShot1();
}

void UArcherAnimInstance::AnimNotify_FlippingShot2()
{
	if (Archer)
		Archer->FlippingShot2();
}

void UArcherAnimInstance::AnimNotify_FlippingShot3()
{
	if (Archer)
		Archer->FlippingShot3();
}

void UArcherAnimInstance::AnimNotify_CreateAfterimage()
{
	if (Archer)
		Archer->CreateAfterimage();
}

void UArcherAnimInstance::AnimNotify_Pause()
{
	UAnimMontage * CurrentMontage = GetCurrentActiveMontage();
	if (CurrentMontage)
		Montage_Pause(CurrentMontage);
}

void UArcherAnimInstance::AnimNotify_ArrowShowerShot()
{
	if (Archer)
		Archer->ArrowShowerShot();
}

void UArcherAnimInstance::AnimNotify_PulseShot()
{
	if (Archer)
		Archer->PulseShot();
}

void UArcherAnimInstance::AnimNotify_PulseShotFootDecalSpawn()
{
	if (Archer)
		Archer->SpawnPulseShotFootDecal();
}

void UArcherAnimInstance::AnimNotify_CheckEnemyOverlap()
{
	if (CurSkill)
		CurSkill->CheckEnemyOverlap();
}

void UArcherAnimInstance::ANimNotify_StartMultiHitSkillEnemyOverlap()
{
	if (CurSkill)
		CurSkill->StartMutliHitSkillEnemyOverlap();
}

void UArcherAnimInstance::ANimNotify_SetNormalState()
{
	if (Archer)
		Archer->SetNormalState();
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
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BASICATTACK_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/BasicAttackMontage.BasicAttackMontage"));
	if (BASICATTACK_MONTAGE.Succeeded())
		BasicAttackMontage = BASICATTACK_MONTAGE.Object;
	//-------------------------------------------

	//MoveSkill Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MOVESKILL_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/MoveSkillMontage.MoveSkillMontage"));
	if (MOVESKILL_MONTAGE.Succeeded())
		MoveSkillMontage = MOVESKILL_MONTAGE.Object;
	//-------------------------------------------

	//Desperado Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DESPERADO_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/DesperadoMontage.DesperadoMontage"));
	if (DESPERADO_MONTAGE.Succeeded())
		DesperadoMontage = DESPERADO_MONTAGE.Object;
	//-------------------------------------------

	//KickShot Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> KICKSHOT_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/KickShotMontage.KickShotMontage"));
	if (KICKSHOT_MONTAGE.Succeeded())
		KickShotMontage = KICKSHOT_MONTAGE.Object;
	//-------------------------------------------

	//FlippingArrow Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FLIPPINGARROW_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/FlippingArrowMontage.FlippingArrowMontage"));
	if (FLIPPINGARROW_MONTAGE.Succeeded())
		FlippingArrowMontage = FLIPPINGARROW_MONTAGE.Object;
	//-------------------------------------------

	//ArrowShower Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ARROWSHOWER_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/ArrowShowerMontage.ArrowShowerMontage"));
	if (ARROWSHOWER_MONTAGE.Succeeded())
		ArrowShowerMontage = ARROWSHOWER_MONTAGE.Object;
	//-------------------------------------------

	//PulseShot Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PULSESHOT_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/PulseShotMontage.PulseShotMontage"));
	if (PULSESHOT_MONTAGE.Succeeded())
		PulseShotMontage = PULSESHOT_MONTAGE.Object;
	//-------------------------------------------

	//DiveShot Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DIVESHOT_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/DiveShotMontage.DiveShotMontage"));
	if (DIVESHOT_MONTAGE.Succeeded())
		DiveShotMontage = DIVESHOT_MONTAGE.Object;
	//-------------------------------------------

	//DiveShot Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> STIFFHIT_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/StiffHitMontage.StiffHitMontage"));
	if (STIFFHIT_MONTAGE.Succeeded())
		StiffHitMontage = STIFFHIT_MONTAGE.Object;
	//-------------------------------------------

	//KnockBack Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> KNOCKBACK_MONTAGE(TEXT("/Game/GamePlay/Player/Archer/Animation/KnockBackMontage.KnockBackMontage"));
	if (KNOCKBACK_MONTAGE.Succeeded())
		KnockBackMontage = KNOCKBACK_MONTAGE.Object;
	//-------------------------------------------
}


