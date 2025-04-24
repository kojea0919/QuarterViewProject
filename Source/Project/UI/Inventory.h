// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitInventory();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	TArray<class UInventorySlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventorySlot> InventorySlotClass;

	const int InventorySlotNum = 24;
};
