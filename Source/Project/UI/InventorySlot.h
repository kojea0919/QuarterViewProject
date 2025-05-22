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
	void SetIndex(int Idx) { SlotIdx = Idx; }
protected:
	virtual void NativeConstruct() override;

private:
	void ClearSlot();

private:
	UFUNCTION()
	void ClickButton();	//아이템 사용 버튼 클릭

	UFUNCTION()
	void HoveredButton();	//아이템 툴팁 보여주기

	UFUNCTION()
	void UnHoveredButton();	//아이템 툴팁 숨기기

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* QuantityText;

	UPROPERTY()
	class UButton* SlotButton;

	UPROPERTY()
	class UBaseItem* Item;
	
	UPROPERTY()
	class UInventory* Inventory;

	bool Empty;				//슬롯의 상태

	int SlotIdx;			//현재 Slot의 인덱스
};
