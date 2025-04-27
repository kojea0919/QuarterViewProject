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
	void SetItemInfo(FString ItemName, FString Description, int Price, int ArmorStat);

private:
	FArmorItemInfoStruct ItemInfo;
};
