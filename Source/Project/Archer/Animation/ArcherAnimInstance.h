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

	//�⺻ ���� Montage ���, ����
	//-----------------------------
	void PlayBasicAttackMontage();
	void StopBasicAttackMontage();
	//-----------------------------

	//�ش� Section �⺻ ���� Montage ���
	void PlayBasicAttackMontageSection(int32 NewSection);

	//�̵� ��ų Montage ���
	void PlayMoveSkillMontage();

	//���� ���� ���� ComboSkill Montage�� �ش� Section ���
	void PlayComboSkillMontageSection(int32 NewSection);

	//SkillMontage�� ������ ȣ��� �Լ�(SkillMontageEnd�Լ�)�� Bind
	void BindSkillMontageEndDelegate(UAnimMontage* SkillMontage);


	//��ų Montage ���, ����
	//-----------------------------
	void PlayDesperadoMontage();
	void StopDesperadoMontage();
	//-----------------------------

	//��ų Montage Get�Լ�
	//-----------------------------
	UAnimMontage* GetDesperadoMontage() const { return DesperadoMontage; }
	//-----------------------------

public:
	void SetCurSkill(class UBaseSkill* Skill) { CurSkill = Skill; }

private:
	//AttackComboCheck Notify�� ������ ȣ���� �Լ�
	UFUNCTION()
	void AnimNotify_BasicAttackComboCheck();

	//AttackInputCheckStart Notify�� ������ ȣ���� �Լ�
	UFUNCTION()
	void AnimNotify_BasicAttackInputCheckStart();

	//�⺻���� AnimNotify
	UFUNCTION()
	void AnimNotify_BasicAttackShoot();

	//MoveSkill ���� �ٴ� Decal ����
	UFUNCTION()
	void AnimNotify_MoveSkillFootDecalSpawn();

	UFUNCTION()
	void AnimNotify_RemoveMoveSkillFootDirt();

	UFUNCTION()
	void Animnotify_CreateMoveSkillFootDirt();

	//���� ���� ���� Skill Montage�� ���� �� ȣ��� �Լ�
	void SkillMontageEnd(UAnimMontage*, bool);

	//�÷��̾ �̵� ���� ���·� ����
	UFUNCTION()
	void AnimNotify_PlayerMovable();

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

	class AArcher* Archer;

	class UBaseSkill* CurSkill;
};
