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

	//스킬 사용 관련 함수
	//---------------------------
	virtual bool Use();				//스킬키가 눌리면 호출될 함수
	virtual void ReleaseSkill() {};	//스킬키가 떼지면 호출될 함수
	virtual void End();				//스킬 애니메이션이 끝나면 호출될 함수

	void StartCoolDown();			//스킬 사용시 CoolDown 적용 함수
	void EndCoolDown();				//CoolTime이 끝나면 호출될 함수
	//---------------------------

public:
	void SetMontage(UAnimMontage* InitMontage) { SkillMontage = InitMontage; }
	void SetAnimInstance(class UArcherAnimInstance* InitAnimInstance) { AnimInstance = InitAnimInstance; }

	void SetBaseClass(class AArcher* InitClass) { if (nullptr == Archer) Archer = InitClass; }

	void ResumeMontage();
	void StopMontage();

	UAnimMontage* GetSkillMontage()const { return SkillMontage; }

	//Effect를 꺼야 하는 Skill인 경우 호출 될 함수
	virtual void ReleaseEffect() {}

	//해당 Section Animation재생
	void PlaySkillMontageSection(int32 NewSection);

	//해당 애니메이션 Montage가 재생되고 있으면 true
	bool IsPlayingMontage();

	//UI용 Texture반환 함수
	UMaterialInstanceDynamic* GetUIMaterial() const { return SkillUIMaterial; }

	//Slot Key
	//------------------------------------------------------------
	//void SetQuickSlotKey(ESkillQuickSlot Key) { SlotKey = Key; }
	//ESkillQuickSlot GetQuickSlotKey() const { return SlotKey; }
	//------------------------------------------------------------

	//CoolTime
	//------------------------------------------------------------

	//초기 CoolTime Setting함수
	void SetCoolTime(float Time) { CoolTime = FMath::Clamp(Time, 0.0f, MAX_FLT); }

	//현재 쿨타임이 진행 중인지 알려주는 함수
	bool IsCoolDownActive() const { return IsCoolDown; }

	//쿨타임 Update
	void UpdateCoolDownEffect(float DeltaTime);

	//남은 쿨타임 반환
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

	//스킬 UI Material
	UMaterialInstanceDynamic* SkillUIMaterial;

	//스킬 Slot Key
	//ESkillQuickSlot SlotKey;

	//현재 스킬인 궁극기 인지 나타내는 변수
	bool IsUltimateSkill;

private:
	UAnimMontage* SkillMontage;

	//쿨타임 관련 변수
	//------------------------
	float CoolTime;			//쿨타임
	float ElapsedSkillTime;	//스킬 사용 후 누적 시간

	bool IsCoolDown;		//쿨타임 적용 중인지 나타내는 변수

	FTimerHandle CooldownTimerHandle;//쿨타임 적용하기 위한 FTimerHandle
	//------------------------

	//스킬 QuickSlot
	class USkillQuickSlot* CurSlot;
	
};
