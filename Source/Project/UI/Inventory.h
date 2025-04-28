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

	void AddItem(class UBaseItem * Item);

	void SetPlayer(class AArcher* Player) { CurrentPlayer = Player; }

	void EquipItem(class UBaseItem* Item);

	bool IsCanAdd() { return  CurrentItemNum < InventorySlotNum; }

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ClickExitButton();	//나가기 버튼 클릭

private:
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	TArray<class UInventorySlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventorySlot> InventorySlotClass;

	UPROPERTY()
	class UButton* ExitButton;

	const int InventorySlotNum = 20;
	int CurrentItemNum = 0;

	class AArcher* CurrentPlayer;
};
