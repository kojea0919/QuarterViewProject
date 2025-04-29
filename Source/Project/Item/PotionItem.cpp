// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"

UPotionItem::UPotionItem()
	: UBaseItem(EItemListType::Potion)
{
}

UBaseItem* UPotionItem::GetCopyItem()const
{
	UPotionItem* NewItem = NewObject<UPotionItem>();
	NewItem->ItemInfo = ItemInfo;
	NewItem->CurrentItemInfo = &NewItem->ItemInfo;
	NewItem->ItemTexture = ItemTexture;
	NewItem->Quantity = Quantity;
	NewItem->ItemType = ItemType;

	return NewItem;
}

void UPotionItem::SetItemInfo(FString ItemName, FString Description, int Price, int HealAmount)
{
	ItemInfo.ItemName = ItemName;
	ItemInfo.Description = Description;
	ItemInfo.Price = Price;
	ItemInfo.HealAmount = HealAmount;

	CurrentItemInfo = &ItemInfo;
}
