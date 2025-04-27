// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ItemStruct.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPotionItem : public UBaseItem
{
	GENERATED_BODY()
	
public:
	UPotionItem();

public:
	void SetItemInfo(FString ItemName, FString Description, int Price, int HealAmount);

private:
	FConsumptionItemInfoStruct ItemInfo;

	int Quantity;			//회복아이템 개수
};
