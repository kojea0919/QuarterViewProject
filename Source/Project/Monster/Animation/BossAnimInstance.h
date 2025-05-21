// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UBossAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();

public:
	void PlayBasicComboAttackMontage();
	void PlaySpawnSawToothMontage();
	void PlaySpawnMeteorMontage();
	void PlayDashSkillStartMontae();
	void PlayBigSwingMontage();
	void PlayStoneSpikeMontage();
	void PlayDomainExpansion();
	void PlaySoulSiphon();
	void PlaySoulSiphonEnd();
	void PlayStunLoop();

	void StopCurMontage();
private:
	UFUNCTION()
	void AnimNotify_RotateStart();

	UFUNCTION()
	void AnimNotify_RotateEnd();

	UFUNCTION()
	void AnimNotify_BasicAttackComboCheck();

	UFUNCTION()
	void AnimNotify_SpawnSawTooth();

	UFUNCTION()
	void AnimNotify_ReadyToSpawnMeteor();

	UFUNCTION()
	void AnimNotify_SpawnMeteor();

	UFUNCTION()
	void AnimNotify_BossDash();

	UFUNCTION()
	void AnimNotify_SpawnStoneSpikeMarkEffect();

	UFUNCTION()
	void AnimNotify_SpawnDomainExpansion();

	UFUNCTION()
	void AnimNotify_CheckSoulSiphonOverlap();

	UFUNCTION()
	void AnimNotify_SoulSiphonEnd();
	
	UFUNCTION()
	void AnimNotify_SpawnBigSwingAreaMarkEffect();

	UFUNCTION()
	void AnimNotify_CheckBigSwingOverlap();

	UFUNCTION()
	void AnimNotify_StartBehaviorTree();


private:
	void InitMontage();

	void PlayBasicComboAttackMontageSection(int32 NewSection);

private:
	UFUNCTION()
	void BossMontageEnd(UAnimMontage* Montage, bool value);

	UFUNCTION()
	void BossSoulSiphonEndMontageEnd(UAnimMontage* Montage, bool value);

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* BasicComboAttackMontage;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpawnSawToothMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpawnMeteorMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DashSkillStartMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* BigSwingMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* StoneSpikeMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DomainExpansionMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SoulSiphonMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SoulSiphonEndMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	UAnimMontage* StunLoopMontage;

private:
	class ABoss* Boss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
};
