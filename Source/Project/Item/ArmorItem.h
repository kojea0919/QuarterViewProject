// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ItemStruct.h"
#include "ArmorItem.generated.h"

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

	int GetArmorStat() const { return ItemInfo.ArmorStat; }

private:
	EArmorType ArmorType;
};
