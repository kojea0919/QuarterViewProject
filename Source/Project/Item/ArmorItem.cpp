// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ArmorItem.h"

UArmorItem::UArmorItem()
	: UBaseItem(EItemListType::Armor)
{
}

void UArmorItem::SetItemInfo(FString ItemName, FString Description, int Price, int ArmorStat, EArmorType Type)
{
	ItemInfo.ItemName = ItemName;
	ItemInfo.Description = Description;
	ItemInfo.Price = Price;
	ItemInfo.ArmorStat = ArmorStat;

	CurrentItemInfo = &ItemInfo;

	ArmorType = Type;
}

UBaseItem* UArmorItem::GetCopyItem() const
{
	UArmorItem* NewItem = NewObject<UArmorItem>();
	NewItem->ItemInfo = ItemInfo;
	NewItem->CurrentItemInfo = &NewItem->ItemInfo;
	NewItem->ItemTexture = ItemTexture;
	NewItem->Quantity = Quantity;
	NewItem->ItemType = ItemType;

	NewItem->ArmorType = ArmorType;

	return NewItem;
}
