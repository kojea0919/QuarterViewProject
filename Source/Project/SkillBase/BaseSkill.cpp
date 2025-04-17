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
	//�ٸ� ��ų �߿��� ���� �Ұ���
	if (Archer->GetMoveSkillOn() || Archer->GetUseSkill())
		return false;

	if (!AnimInstance->Montage_IsPlaying(SkillMontage))
	{
		Archer->SetUseSkill(true);
		AnimInstance->Montage_Play(SkillMontage);

		//AnimInstnace�� BindSkillMontageEndDeleegate�Լ��� ȣ���ؼ�
		//Animation�� ������ Skill�� End�Լ��� ȣ���ϵ��� �Ѵ�.
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
	//��� �ð� ������Ʈ
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
	//��ٿ��� ���� ������ ���� ��쿡�� ����
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


