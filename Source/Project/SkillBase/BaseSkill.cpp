// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/Animation/ArcherAnimInstance.h"
#include "Project/UI/SkillQuickSlot.h"

UBaseSkill::UBaseSkill()
	: Archer(nullptr), IsUltimateSkill(false), CoolTime(1.0f), IsCoolDown(false), CurSlot(nullptr)
{
}

bool UBaseSkill::Use()
{
	//다른 스킬 중에는 공격 불가능
	if (Archer->GetMoveSkillOn() || Archer->GetUseSkill())
		return false;

	if (!AnimInstance->Montage_IsPlaying(SkillMontage))
	{
		Archer->SetUseSkill(true);
		AnimInstance->Montage_Play(SkillMontage);

		//AnimInstnace의 BindSkillMontageEndDeleegate함수를 호출해서
		//Animation이 끝나면 Skill의 End함수를 호출하도록 한다.
		AnimInstance->BindSkillMontageEndDelegate(SkillMontage);
		AnimInstance->SetCurSkill(this);
		return true;
	}

	return false;
}

void UBaseSkill::End()
{
	if (Archer)
		Archer->SetMoveAble(true);
}

void UBaseSkill::ResumeMontage()
{
	if (SkillMontage)
		AnimInstance->Montage_Resume(SkillMontage);
}

void UBaseSkill::StopMontage()
{
	if (SkillMontage)
		AnimInstance->Montage_Stop(0.2f, SkillMontage);
}

void UBaseSkill::PlaySkillMontageSection(int32 NewSection)
{
	if (SkillMontage)
		AnimInstance->PlayComboSkillMontageSection(NewSection);
}

bool UBaseSkill::IsPlayingMontage()
{
	if (SkillMontage)
		return AnimInstance->Montage_IsPlaying(SkillMontage);
	return false;
}

void UBaseSkill::UpdateCoolDownEffect(float DeltaTime)
{
	//경과 시간 업데이트
	//---------------------------------------------
	ElapsedSkillTime += DeltaTime;

	float CurPercent = ElapsedSkillTime / CoolTime;
	//---------------------------------------------

	CurPercent = FMath::Clamp(CurPercent, 0.0f, 1.0f);

	SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), CurPercent);
}

void UBaseSkill::SetMaterial(const TCHAR* FileName)
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, FileName);

	SkillUIMaterial = UMaterialInstanceDynamic::Create(Material, this);

	SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), 0.0f);
}

void UBaseSkill::SetQuickSlot(USkillQuickSlot* Slot)
{
	if (Slot->IsValidLowLevel())
		CurSlot = Slot;
}

void UBaseSkill::StartCoolDown()
{
	//쿨다운이 적용 중이지 않은 경우에만 실행
	if (!IsCoolDown)
	{
		Archer->GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this,
			&UBaseSkill::EndCoolDown, CoolTime, false);
		IsCoolDown = true;
		ElapsedSkillTime = 0.0f;

		CurSlot->SetRemainCoolTimeVisible(true);
	}
}

void UBaseSkill::EndCoolDown()
{
	IsCoolDown = false;
	ElapsedSkillTime = 0.0f;

	SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), 0.0f);

	CurSlot->SetRemainCoolTimeVisible(false);
	CurSlot->PlaySkillCoolTimeEndAnimation();
}


