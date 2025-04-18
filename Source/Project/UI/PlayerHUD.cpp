// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "SkillQuickSlot.h"
#include "Project/SkillBase/BaseSkill.h"

void UPlayerHUD::SetQuickSlotSkill(UBaseSkill* Skill, ESkillQuickSlot SlotKey)
{
	if (nullptr == Skill)
		return;

	uint8 SlotIdx = (uint8)SlotKey;

	//범위 내에 있는 경우에 Key Setting
	bool bIsIn = FMath::IsWithin<uint8>(SlotIdx, (uint8)ESkillQuickSlot::SlotQ, (uint8)ESkillQuickSlot::SlotMax);

	if (bIsIn)
	{
		//Slot에 Skill Setting
		USkillQuickSlot* TargetSlot = SkillQuickSlotArr[SlotIdx];
		TargetSlot->SetSkill(Skill);

		//Skill에 Slot Setting
		Skill->SetQuickSlot(TargetSlot);
	}
}

void UPlayerHUD::UseSkill(ESkillQuickSlot SlotKey)
{
	uint8 SlotIdx = (uint8)SlotKey;

	//올바른 Key인 경우 해당 슬롯의 스킬 사용
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

	//올바른 Key인 경우 해당 슬롯의 스킬 해제
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
