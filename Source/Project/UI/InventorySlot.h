// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItem(class UBaseItem* NewItem);
	bool IsEmpty() const { return Empty; }

	FString GetItemName();

	int GetQuantity();
	void SetQuantity(int Num);

	void SetInventory(class UInventory* Inven) { Inventory = Inven; }

protected:
	virtual void NativeConstruct() override;

private:
	void ClearSlot();

private:
	UFUNCTION()
	void ClickButton();	//아이템 사용 버튼 클릭

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* QuantityText;

	UPROPERTY()
	class UButton* SlotButton;

	class UBaseItem* Item;
	
	class UInventory* Inventory;

	int Quantity;

	bool Empty;
};
