// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WeaponItem.h"

void UWeaponItem::SetItemInfo(FString ItemName, FString Description,int Price, int AttackStat, int CriticalStat)
{
	ItemInfo.ItemName = ItemName;
	ItemInfo.Description = Description;
	ItemInfo.Price = Price;
	ItemInfo.AttackStat = AttackStat;
	ItemInfo.CriticalStat = CriticalStat;

	CurrentItemInfo = &ItemInfo;
}
