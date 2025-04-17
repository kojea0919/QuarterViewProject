// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBaseSkill : public UObject
{
	GENERATED_BODY()

public:
	UBaseSkill();

	//��ų ��� ���� �Լ�
	//---------------------------
	virtual bool Use();				//��ųŰ�� ������ ȣ��� �Լ�
	virtual void ReleaseSkill() {};	//��ųŰ�� ������ ȣ��� �Լ�
	virtual void End();				//��ų �ִϸ��̼��� ������ ȣ��� �Լ�

	void StartCoolDown();			//��ų ���� CoolDown ���� �Լ�
	void EndCoolDown();				//CoolTime�� ������ ȣ��� �Լ�
	//---------------------------

public:
	void SetMontage(UAnimMontage* InitMontage) { SkillMontage = InitMontage; }
	void SetAnimInstance(class UArcherAnimInstance* InitAnimInstance) { AnimInstance = InitAnimInstance; }

	void SetBaseClass(class AArcher* InitClass) { if (nullptr == Archer) Archer = InitClass; }

	void ResumeMontage();
	void StopMontage();

	UAnimMontage* GetSkillMontage()const { return SkillMontage; }

	//Effect�� ���� �ϴ� Skill�� ��� ȣ�� �� �Լ�
	virtual void ReleaseEffect() {}

	//�ش� Section Animation���
	void PlaySkillMontageSection(int32 NewSection);

	//�ش� �ִϸ��̼� Montage�� ����ǰ� ������ true
	bool IsPlayingMontage();

	//UI�� Texture��ȯ �Լ�
	UMaterialInstanceDynamic* GetUIMaterial() const { return SkillUIMaterial; }

	//Slot Key
	//------------------------------------------------------------
	//void SetQuickSlotKey(ESkillQuickSlot Key) { SlotKey = Key; }
	//ESkillQuickSlot GetQuickSlotKey() const { return SlotKey; }
	//------------------------------------------------------------

	//CoolTime
	//------------------------------------------------------------

	//�ʱ� CoolTime Setting�Լ�
	void SetCoolTime(float Time) { CoolTime = FMath::Clamp(Time, 0.0f, MAX_FLT); }

	//���� ��Ÿ���� ���� ������ �˷��ִ� �Լ�
	bool IsCoolDownActive() const { return IsCoolDown; }

	//��Ÿ�� Update
	void UpdateCoolDownEffect(float DeltaTime);

	//���� ��Ÿ�� ��ȯ
	float GetRemainCoolTime() const { return CoolTime - ElapsedSkillTime; }
	//------------------------------------------------------------

	void SetMaterial(const TCHAR* FileName);

	//Slot Setting
	//------------------------------------------------------------
	void SetQuickSlot(class USkillQuickSlot* Slot);
	void SetEmptySlot() { CurSlot = nullptr; }
	//------------------------------------------------------------

	bool GetIsUltimateSkill() const { return IsUltimateSkill; }

protected:
	class AArcher* Archer;

	class UArcherAnimInstance* AnimInstance;

	//��ų UI Material
	UMaterialInstanceDynamic* SkillUIMaterial;

	//��ų Slot Key
	//ESkillQuickSlot SlotKey;

	//���� ��ų�� �ñر� ���� ��Ÿ���� ����
	bool IsUltimateSkill;

private:
	UAnimMontage* SkillMontage;

	//��Ÿ�� ���� ����
	//------------------------
	float CoolTime;			//��Ÿ��
	float ElapsedSkillTime;	//��ų ��� �� ���� �ð�

	bool IsCoolDown;		//��Ÿ�� ���� ������ ��Ÿ���� ����

	FTimerHandle CooldownTimerHandle;//��Ÿ�� �����ϱ� ���� FTimerHandle
	//------------------------

	//��ų QuickSlot
	class USkillQuickSlot* CurSlot;
	
};
