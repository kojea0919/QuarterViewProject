// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "SkillQuickSlot.h"
#include "SkillGaugeBar.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Store.h"
#include "SkillBase/BaseSkill.h"
#include "StoreWidgetDrag.h"
#include "BossClear.h"
#include "BossHPBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

void UPlayerHUD::SetVisibilityIntersectionKey(bool Enable)
{
	if (IntersectionKey)
	{
		if (Enable)
			IntersectionKey->SetVisibility(ESlateVisibility::Visible);
		else
			IntersectionKey->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerHUD::SetVisibilityInventory()
{
	if (!Inventory->IsValidLowLevel())
		return; 

	if (Inventory->IsVisible())
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	else
		Inventory->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHUD::SetVisibilityEquipment()
{
	if (!Equipment->IsValidLowLevel())
		return;

	if (Equipment->IsVisible())
		Equipment->SetVisibility(ESlateVisibility::Hidden);
	else
		Equipment->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHUD::SetVisibilityStore()
{
	if (Store->IsValidLowLevel())
	{
		//NPC의 아이템 리스트를 읽어서 Slot에 Setting
		Store->SetItemSlot();

		Store->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerHUD::SetVisibilityBossClear()
{
	if (BossClear->IsValidLowLevel())
	{
		BossClear->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerHUD::SetVisibilityBossHPBar(bool Enable)
{
	if (BossHPBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("Call"));
		if (Enable)
			BossHPBar->SetVisibility(ESlateVisibility::Visible);
		else
			BossHPBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UPlayerHUD::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UStoreWidgetDrag * WidgetDrag = Cast<UStoreWidgetDrag>(InOperation);
	if (nullptr == WidgetDrag)
		return false;

	UUserWidget* WidgetReference = WidgetDrag->GetReference();
	if (nullptr == WidgetReference)
		return false;

	FVector2D DragOffset = WidgetDrag->GetDragOffset();

	FVector2D Pos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

	WidgetReference->RemoveFromParent();
	WidgetReference->AddToViewport();
	WidgetReference->SetPositionInViewport(Pos - DragOffset, false);

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UPlayerHUD::SetupStoreUI(AStoreNPC* Npc,AArcher * Player)
{
	if (nullptr != Store)
	{
		Store->SetStoreNPC(Npc);
		Store->SetPlayer(Player);
	}
}

void UPlayerHUD::SetBossMaxHP(float HP)
{
	if (BossHPBar)
		BossHPBar->SetBossMaxHP(HP);
}

void UPlayerHUD::SetBossCurrentHP(float newHP)
{
	if (BossHPBar)
		BossHPBar->SetBossCurrentHP(newHP);
}

void UPlayerHUD::InitBossHP()
{
	if (BossHPBar)
		BossHPBar->InitBossHP();
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

	QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotR")));
	if(QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("R"));
	}

	QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotD")));
	if (QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("D"));
	}

	QuickSlot = Cast<USkillQuickSlot>(GetWidgetFromName(TEXT("UI_QuickSlotF")));
	if (QuickSlot)
	{
		SkillQuickSlotArr.Push(QuickSlot);
		QuickSlot->SetSlotKeyText(TEXT("F"));
	}

	SkillGaugeBar = Cast<USkillGaugeBar>(GetWidgetFromName(TEXT("UI_SkillGaugeBar")));

	IntersectionKey = Cast<UUserWidget>(GetWidgetFromName(TEXT("UI_IntersectionKey")));
	if (IntersectionKey)
		IntersectionKey->SetVisibility(ESlateVisibility::Hidden);


	//인벤토리 초기화
	//---------------------------------------------------------------
	Inventory = Cast<UInventory>(GetWidgetFromName(TEXT("UI_Inventory")));
	if (Inventory)
	{
		Inventory->InitInventory();
		Inventory->SetVisibility(ESlateVisibility::Hidden);
	}
	//---------------------------------------------------------------

	//장비창 초기화
	//---------------------------------------------------------------
	Equipment = Cast<UEquipment>(GetWidgetFromName(TEXT("UI_Equipment")));
	if (Equipment)
	{
		Equipment->SetVisibility(ESlateVisibility::Hidden);
	}
	//---------------------------------------------------------------
	
	//상점UI 초기화
	//---------------------------------------------------------------
	Store = Cast<UStore>(GetWidgetFromName(TEXT("UI_Store")));
	if (Store)
	{
		Store->InitStore();
		Store->SetVisibility(ESlateVisibility::Hidden);
	}
	//---------------------------------------------------------------

	//보스Clear창 초기화
	//---------------------------------------------------------------
	BossClear = Cast<UBossClear>(GetWidgetFromName(TEXT("UI_BossClear")));
	if (BossClear)
	{
		BossClear->SetVisibility(ESlateVisibility::Hidden);
	}
	//---------------------------------------------------------------

	//보스 체력 UI
	//---------------------------------------------------------------
	BossHPBar = Cast<UBossHPBar>(GetWidgetFromName(TEXT("UI_BossHPBar")));
	if (BossHPBar)
	{
		BossHPBar->SetVisibility(ESlateVisibility::Hidden);
	}
	//---------------------------------------------------------------
}
