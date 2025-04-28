// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ItemStruct.h"
#include "ArmorItem.generated.h"

//현재 아이템 타입
//------------------------------
enum class EArmorType
{
	Hat = 0,
	Chest,
	Pants,
	Glove,
	Max
};
//------------------------------

/**
 * 
 */
UCLASS()
class PROJECT_API UArmorItem : public UBaseItem
{
	GENERATED_BODY()

public:
	UArmorItem();

public:
	void SetItemInfo(FString ItemName, FString Description, int Price, int ArmorStat,EArmorType Type);

	virtual class UBaseItem* GetCopyItem() const override;
	EArmorType GetArmorType() { return ArmorType; }

private:
	FArmorItemInfoStruct ItemInfo;

	EArmorType ArmorType;
};
