// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Item/BaseItem.h"
#include "Inventory.h"

void UInventorySlot::SetItem(UBaseItem* NewItem)
{
	if (NewItem)
	{
		if (ItemImage)
		{
			ItemImage->SetBrushFromTexture(NewItem->GetTexture());
			ItemImage->SetVisibility(ESlateVisibility::Visible);
		}
		Empty = false;
		Quantity = NewItem->GetQuantity();
		Item = NewItem;

		//포션인 경우에만 개수 표기
		//-------------------------------------------------------------
		if (NewItem->GetItemType() == EItemListType::Potion)
		{
			if (QuantityText)
			{
				QuantityText->SetText(FText::AsNumber(Quantity));
				QuantityText->SetVisibility(ESlateVisibility::Visible);
			}
		}
		//-------------------------------------------------------------
	}
}

FString UInventorySlot::GetItemName()
{
	if (Item)
		return Item->GetItemName();
	return FString();
}

int UInventorySlot::GetQuantity()
{
	if (Item)
		return Item->GetQuantity();
	return -1;
}

void UInventorySlot::SetQuantity(int Num)
{
	if (Item)
	{
		Item->SetQuantity(Num);
		if (QuantityText)
		{
			QuantityText->SetText(FText::AsNumber(Num));
		}
	}
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	if (ItemImage)
		ItemImage->SetVisibility(ESlateVisibility::Hidden);

	QuantityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("QuantityText")));
	if (QuantityText)
		QuantityText->SetVisibility(ESlateVisibility::Hidden);

	SlotButton = Cast<UButton>(GetWidgetFromName(TEXT("SlotButton")));
	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UInventorySlot::ClickButton);
		SlotButton->OnHovered.AddDynamic(this, &UInventorySlot::HoveredButton);
		SlotButton->OnUnhovered.AddDynamic(this, &UInventorySlot::UnHoveredButton);
	}

	Quantity = 0;
	Empty = true;
}

void UInventorySlot::ClearSlot()
{
	Empty = true;
	Quantity = 0;
	Item = nullptr;

	if(QuantityText)
		QuantityText->SetVisibility(ESlateVisibility::Hidden);

	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(nullptr);
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInventorySlot::ClickButton()
{
	if (Empty)
		return;

	//포션이면 개수를 줄여주고 0개가 되면 슬롯 비우기
	if (Item->GetItemType() == EItemListType::Potion)
	{
		int CurQuantity = Item->GetQuantity();
		--CurQuantity;
		SetQuantity(CurQuantity);
		if (CurQuantity != 0)
		{
			return;
		}
	}

	//장비 아이템 장착
	//-----------------------------------------------
	else
	{
		if (Inventory)
		{
			Inventory->EquipItem(Item);
		}
	}
	//-----------------------------------------------

	ClearSlot();

}

void UInventorySlot::HoveredButton()
{
	if (Empty)
		return;

	if (Inventory)
	{
		Inventory->ShowInventoryItemToolTip(Item);
	}
}

void UInventorySlot::UnHoveredButton()
{
	if (Empty)
		return;

	if (Inventory)
		Inventory->HideInventoryItemToolTip();
}
