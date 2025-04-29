// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemStruct.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UWeaponItem : public UBaseItem
{
	GENERATED_BODY()

public:
	UWeaponItem();

public:
	void SetItemInfo(FString ItemName, FString Description,int Price, int AttackStat, int CriticalStat);
	
	virtual class UBaseItem* GetCopyItem() const override;

	int GetAttackStat() const { return ItemInfo.AttackStat; }
	int GetCriticalStat() const { return ItemInfo.CriticalStat; }

private:
	FWeaponItemInfoStruct ItemInfo;
};
