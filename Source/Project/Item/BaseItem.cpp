// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

UBaseItem::UBaseItem()
{
}

UBaseItem::UBaseItem(EItemListType Type)
{
	ItemInfo.ItemType = Type;
}

const FBaseItemInfoStruct& UBaseItem::GetItemInfo() const
{
	return ItemInfo;
}

const FString& UBaseItem::GetItemName() const
{
	return ItemInfo.ItemName;
}
