// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "SkillQuickSlot.h"
#include "Project/SkillBase/BaseSkill.h"

void UPlayerHUD::SetQuickSlotSkill(UBaseSkill* Skill, ESkillQuickSlot SlotKey)
{
	if (nullptr == Skill)
		return;

	uint8 SlotIdx = (uint8)SlotKey;

	//���� ���� �ִ� ��쿡 Key Setting
	bool bIsIn = FMath::IsWithin<uint8>(SlotIdx, (uint8)ESkillQuickSlot::SlotQ, (uint8)ESkillQuickSlot::SlotMax);

	if (bIsIn)
	{
		//Slot�� Skill Setting
		USkillQuickSlot* TargetSlot = SkillQuickSlotArr[SlotIdx];
		TargetSlot->SetSkill(Skill);

		//Skill�� Slot Setting
		Skill->SetQuickSlot(TargetSlot);
	}
}

void UPlayerHUD::UseSkill(ESkillQuickSlot SlotKey)
{
	uint8 SlotIdx = (uint8)SlotKey;

	//�ùٸ� Key�� ��� �ش� ������ ��ų ���
	//------------------------------------------------------------------
	bool bIsIn = FMath::IsWithin(SlotIdx, (uint8)ESkillQuickSlot::SlotQ, (uint8)ESkillQuickSlot::SlotMax);
	if (bIsIn)
	{
		SkillQuickSlotArr[SlotIdx]->UseSkill();
	}
	//------------------------------------------------------------------
}

void UPlayerHUD::ReleaseSkill(ESkillQuickSlot SlotKey)
{
	uint8 SlotIdx = (uint8)SlotKey;

	//�ùٸ� Key�� ��� �ش� ������ ��ų ����
	//------------------------------------------------------------------
	bool bIsIn = FMath::IsWithin(SlotIdx, (uint8)ESkillQuickSlot::SlotQ, (uint8)ESkillQuickSlot::SlotMax);
	if (bIsIn)
	{
		SkillQuickSlotArr[SlotIdx]->ReleaseSkill();
	}
	//------------------------------------------------------------------
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	USkillQuickSlot * QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotQ")));
	if (QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("Q"));
	}

	QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotW")));
	if (QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("W"));
	}

	QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotE")));
	if (QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("E"));
	}
}
