// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"

void UPotionItem::SetItemInfo(FString ItemName, FString Description, int Price, int HealAmount)
{
	ItemInfo.ItemName = ItemName;
	ItemInfo.Description = Description;
	ItemInfo.Price = Price;
	ItemInfo.HealAmount = HealAmount;

	CurrentItemInfo = &ItemInfo;
}
