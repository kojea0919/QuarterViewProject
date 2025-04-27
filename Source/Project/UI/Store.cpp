// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "StoreSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragImage.h"
#include "StoreDragWidget.h"
#include "StoreWidgetDrag.h"
#include "NPC/StoreNPC.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "Item/PotionItem.h"
#include "ItemPurchaseSlot.h"
#include "PurchaseQuantitySelector.h"

void UStore::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStore::InitStore()
{
	for (size_t i = 0; i < StoreSlotNum; ++i)
	{
		UStoreSlot* StoreSlot = CreateWidget<UStoreSlot>(GetWorld(), StoreSlotClass);
		SlotArr.Push(StoreSlot);
		StoreSlot->SetStore(this);
		if(WrapBox)
			WrapBox->AddChild(StoreSlot);
	}
	
	for (size_t i = 0; i < PurchaseSlotNum; ++i)
	{
		UItemPurchaseSlot* PurchaseSlot = CreateWidget<UItemPurchaseSlot>(GetWorld(), ItemPurchaseSlotClass);
		PurchaseSlot->SetSlotIdx(i);
		PurchaseSlot->SetStore(this);
		PurchaseSlotArr.Push(PurchaseSlot);
		if(ItemPurchaseWaitingWrapBox)
			ItemPurchaseWaitingWrapBox->AddChild(PurchaseSlot);
	}

	PurchaseQuantitySelector = CreateWidget<UPurchaseQuantitySelector>(GetWorld(), PurchaseQuantitySelectorClass);
	if (PurchaseQuantitySelector)
		PurchaseQuantitySelector->SetVisibility(ESlateVisibility::Hidden);

	PurchaseSlotIdx = 0;
}

void UStore::SetItemSlot()
{
	if (CurrentNPC)
	{
		switch (CurrentItemButtonType)
		{
		case EItemListType::Weapon:
			SetItemSlot<UWeaponItem>(CurrentNPC->WeaponItemArr);
			break;
		case EItemListType::Armor:
			SetItemSlot<UArmorItem>(CurrentNPC->ArmorItemArr);
			break;
		case EItemListType::Potion:
			SetItemSlot<UPotionItem>(CurrentNPC->PotionItemArr);
			break;
		default:
			break;
		}
		
	}
}

void UStore::ClickedStoreSlot(const UBaseItem* Item)
{
	if (PurchaseSlotIdx == PurchaseSlotNum)
		return;

	//포션이 아닌 경우에만 바로 추가
	if(CurrentItemButtonType != EItemListType::Potion)
		PurchaseSlotArr[PurchaseSlotIdx++]->SetItem(Item);
	//포션인 경우에는 개수 선택 UI 보여주기
	else
	{
		PurchaseQuantitySelector->SetVisibility(ESlateVisibility::Visible);

	}


}

void UStore::NativeConstruct()
{
	Super::NativeConstruct();

	WrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox")));

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitStoreButton")));
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UStore::ClickExit);
	}

	WeaponButton = Cast<UButton>(GetWidgetFromName(TEXT("WeaponButton")));
	if (WeaponButton)
	{
		WeaponButton->OnClicked.AddDynamic(this, &UStore::ClickWeapon);
	}

	ArmorButton = Cast<UButton>(GetWidgetFromName(TEXT("ArmorButton")));
	if (ArmorButton)
	{
		ArmorButton->OnClicked.AddDynamic(this, &UStore::ClickArmor);
	}

	PotionButton = Cast<UButton>(GetWidgetFromName(TEXT("PotionButton")));
	if (PotionButton)
	{
		PotionButton->OnClicked.AddDynamic(this, &UStore::ClickPotion);
	}

	ItemPurchaseWaitingWrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("ItemPurchaseWaitingWrapBox")));

	CurrentNPC = nullptr;
	CurrentItemButtonType = EItemListType::Weapon;
}

FReply UStore::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 왼쪽 마우스 버튼이 눌렸을 때의 처리
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReplyResult.NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UStore::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//UDragImage* test = CreateWidget<UDragImage>(GetOwningPlayer(), TEST);
	//UStoreDragWidget * DragWidget = CreateWidget<UStoreDragWidget>(GetOwningPlayer(), StoreDragWidgetClass);
	//DragWidget->SetWidgetReference(this);
	UStoreWidgetDrag* WidgetDrag = NewObject<UStoreWidgetDrag>();
	WidgetDrag->SetWidgetReference(this);
	WidgetDrag->SetDragOffset(DragOffset);

	WidgetDrag->DefaultDragVisual = this;
	WidgetDrag->Pivot = EDragPivot::MouseDown;

	OutOperation = WidgetDrag;
}

void UStore::ClickExit()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UStore::ClickWeapon()
{
	CurrentItemButtonType = EItemListType::Weapon;
	SetItemSlot();
}

void UStore::ClickArmor()
{
	CurrentItemButtonType = EItemListType::Armor;
	SetItemSlot();
}

void UStore::ClickPotion()
{
	CurrentItemButtonType = EItemListType::Potion;
	SetItemSlot();
}

void UStore::UpdatePurchaseSlot(int Idx)
{
	for (int idx = Idx + 1; idx < PurchaseSlotIdx; ++idx)
	{
		PurchaseSlotArr[idx - 1]->SetItem(PurchaseSlotArr[idx]->GetItem());
	}
	PurchaseSlotArr[PurchaseSlotIdx - 1]->ClearSlot();
	--PurchaseSlotIdx;
}
