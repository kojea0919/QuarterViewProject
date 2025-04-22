// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArcherAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherAnimInstance : public UAnimInstance
{
	GENERATED_BODY()	

public:
	UArcherAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation();

	//기본 공격 Montage 재생, 정지
	//-----------------------------
	void PlayBasicAttackMontage();
	void StopBasicAttackMontage();
	//-----------------------------

	//해당 Section 기본 공격 Montage 재생
	void PlayBasicAttackMontageSection(int32 NewSection);

	//이동 스킬 Montage 재생
	void PlayMoveSkillMontage();

	//현재 실행 중인 ComboSkill Montage의 해당 Section 재생
	void PlayComboSkillMontageSection(int32 NewSection);

	//SkillMontage가 끝나면 호출될 함수(SkillMontageEnd함수)를 Bind
	void BindSkillMontageEndDelegate(UAnimMontage* SkillMontage);


	//스킬 Montage 재생, 정지
	//-----------------------------
	void PlayDesperadoMontage();
	void StopDesperadoMontage();

	void PlayKickShotMontage();
	void StopKickShotMontage();
	//-----------------------------

	//스킬 Montage Get함수
	//-----------------------------
	UAnimMontage* GetDesperadoMontage() const { return DesperadoMontage; }
	UAnimMontage* GetKickShotMontage() const { return KickShotMontage; }
	UAnimMontage* GetFlippingArrowMontage() const { return FlippingArrowMontage; }
	//-----------------------------

public:
	void SetCurSkill(class UBaseSkill* Skill) { CurSkill = Skill; }
	void SetCurExcuteComboSkill(class UComboSkill* Skill) { CurExcuteComboSkill = Skill; }

private:
	//AttackComboCheck Notify를 받으면 호출할 함수
	UFUNCTION()
	void AnimNotify_BasicAttackComboCheck();

	//AttackInputCheckStart Notify를 받으면 호출할 함수
	UFUNCTION()
	void AnimNotify_BasicAttackInputCheckStart();

	//기본공격 AnimNotify
	UFUNCTION()
	void AnimNotify_BasicAttackShot();

	//MoveSkill 사용시 바닥 Decal 생성
	UFUNCTION()
	void AnimNotify_MoveSkillFootDecalSpawn();

	UFUNCTION()
	void AnimNotify_RemoveMoveSkillFootDirt();

	UFUNCTION()
	void Animnotify_CreateMoveSkillFootDirt();

	//현재 실행 중인 Skill Montage가 끝날 때 호출될 함수
	void SkillMontageEnd(UAnimMontage*, bool);

	//플레이어를 이동 가능 상태로 변경
	UFUNCTION()
	void AnimNotify_PlayerMovable();

	//플레이어를 이동 불가 상태로 변경
	UFUNCTION()
	void AnimNotify_PlayerUnMovalbe();

	//스킬 이펙트 생성
	UFUNCTION()
	void AnimNotify_SpawnDeperadoEffect();

	UFUNCTION()
	void AnimNotify_SkillComboCheck();

	UFUNCTION()
	void AnimNotify_SkillInputCheckStart();

	UFUNCTION()
	void AnimNotify_SpecialAttackShot();

	UFUNCTION()
	void AnimNotify_FlippingShot1();

	UFUNCTION()
	void AnimNotify_FlippingShot2();

	UFUNCTION()
	void AnimNotify_FlippingShot3();

private:
	UFUNCTION()
	void BasicAttackMontageEnd(UAnimMontage* Montage, bool value);

private:
	void InitMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* BasicAttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MoveSkill, Meta = (AllowPrivateAccess = true))
	UAnimMontage* MoveSkillMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DesperadoMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
	UAnimMontage* KickShotMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FlippingArrowMontage;
	
	class AArcher* Archer;

	//현재 사용중인 Skill
	class UBaseSkill* CurSkill;

	//현재 사용중인 ComboSkill
	class UComboSkill* CurExcuteComboSkill;
};
