// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

UBaseItem::UBaseItem()
{
}

UBaseItem::UBaseItem(EItemListType Type)
	: ItemType(Type)
{
}

const FBaseItemInfoStruct& UBaseItem::GetItemInfo() const
{
	return *CurrentItemInfo;
}

const FString& UBaseItem::GetItemName() const
{
	return CurrentItemInfo->ItemName;
}
