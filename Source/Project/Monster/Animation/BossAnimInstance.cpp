// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Animation/BossAnimInstance.h"
#include "Monster/Boss.h"

UBossAnimInstance::UBossAnimInstance()
	: Boss(nullptr)
{
	InitMontage();

}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeInitializeAnimation();

	//CurrentSpeed Setting
	//-------------------------------
	if (Boss)
	{
		CurrentSpeed = Boss->GetVelocity().Size();
	}
	//-------------------------------
}

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ABoss* PawnOwner = Cast<ABoss>(TryGetPawnOwner());
	if (nullptr != PawnOwner)
		Boss = PawnOwner;
}

void UBossAnimInstance::PlayBasicComboAttackMontage()
{
	if (!Montage_IsPlaying(BasicComboAttackMontage))
	{
		Montage_Play(BasicComboAttackMontage);
	}
}

void UBossAnimInstance::PlaySpawnSawToothMontage()
{
	if (!Montage_IsPlaying(SpawnSawToothMontage))
	{
		Montage_Play(SpawnSawToothMontage);
	}
}

void UBossAnimInstance::PlaySpawnMeteorMontage()
{
	if (!Montage_IsPlaying(SpawnMeteorMontage))
	{
		Montage_Play(SpawnMeteorMontage);
	}
}

void UBossAnimInstance::AnimNotify_RotateStart()
{
	if (Boss)
	{
		Boss->SetRotateToPlayer(true);
	}
}

void UBossAnimInstance::AnimNotify_RotateEnd()
{
	if (Boss)
		Boss->SetRotateToPlayer(false);
}

void UBossAnimInstance::AnimNotify_BasicAttackComboCheck()
{
	//플레이어와의 거리가 일정거리 이내면 다음 콤보 진행
	if (Boss && Boss->CanBasicComboAttack())
	{

		int CurrentComboIdx = Boss->GetCurrentBasicCombo();

		CurrentComboIdx = (CurrentComboIdx + 1) % Boss->GetBasicMaxCombo();
		Boss->SetCurrentBasicCombo(CurrentComboIdx);

		PlayBasicComboAttackMontageSection(CurrentComboIdx);
	}
}

void UBossAnimInstance::AnimNotify_SpawnSawTooth()
{
	if (Boss)
	{
		Boss->SpawnSawTooth();
	}
}

void UBossAnimInstance::AnimNotify_ReadyToSpawnMeteor()
{
	if (Boss)
	{
		Boss->ReadyToSpawnMeteor();
	}
}

void UBossAnimInstance::AnimNotify_SpawnMeteor()
{
	if (Boss)
	{
		Boss->SpawnMeteor();
	}
}

void UBossAnimInstance::InitMontage()
{
	//Basic Combo Attck Montage Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BASICCOMBOATTACK_MONTAGE(TEXT("/Game/GamePlay/Enemy/Boss/Animation/BossBasicComboAttackMontage.BossBasicComboAttackMontage"));
	if (BASICCOMBOATTACK_MONTAGE.Succeeded())
	{
		BasicComboAttackMontage = BASICCOMBOATTACK_MONTAGE.Object;
	}
	//-------------------------------------------

	//Spawn Saw Tooth Animation Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWNSAWTOOTH_MONTAGE(TEXT("/Game/GamePlay/Enemy/Boss/Animation/BossSpawnSawToothMontage.BossSpawnSawToothMontage"));
	if (SPAWNSAWTOOTH_MONTAGE.Succeeded())
	{
		SpawnSawToothMontage = SPAWNSAWTOOTH_MONTAGE.Object;
	}
	//-------------------------------------------

	//Spawn Meteor Animation Init
	//-------------------------------------------
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SPAWNMETEOR_MONTAGE(TEXT("/Game/GamePlay/Enemy/Boss/Animation/BossSpawnMeteorMontage.BossSpawnMeteorMontage"));
	if (SPAWNMETEOR_MONTAGE.Succeeded())
	{
		SpawnMeteorMontage = SPAWNMETEOR_MONTAGE.Object;
	}
	//-------------------------------------------
}

void UBossAnimInstance::PlayBasicComboAttackMontageSection(int32 NewSection)
{
	if (!FMath::IsWithinInclusive(NewSection, 0, 2))
		return;

	FName SectionName = *FString::Printf(TEXT("Attack%d"), NewSection + 1);
	Montage_JumpToSection(SectionName);
}
