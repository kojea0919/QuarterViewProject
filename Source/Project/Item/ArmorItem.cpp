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

	ArmorType = Type;
}

UBaseItem* UArmorItem::GetCopyItem() const
{
	UArmorItem* NewItem = NewObject<UArmorItem>();
	NewItem->ItemInfo = ItemInfo;
	
	UTexture2D* NewTexture = LoadObject<UTexture2D>(nullptr, *TexturePath);
	NewItem->ItemTexture = NewTexture;
	NewItem->TexturePath = TexturePath;

	NewItem->Quantity = Quantity;

	NewItem->ArmorType = ArmorType;

	return NewItem;
}
