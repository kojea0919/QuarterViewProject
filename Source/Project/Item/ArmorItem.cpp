// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ArmorItem.h"

void UArmorItem::SetItemInfo(FString ItemName, FString Description, int Price, int ArmorStat)
{
	ItemInfo.ItemName = ItemName;
	ItemInfo.Description = Description;
	ItemInfo.Price = Price;
	ItemInfo.ArmorStat = ArmorStat;

	CurrentItemInfo = &ItemInfo;
}
