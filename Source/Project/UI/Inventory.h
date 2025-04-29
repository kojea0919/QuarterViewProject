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

	class UBaseItem* EquipItem(class UBaseItem* Item);

	bool IsCanAdd() { return  CurrentItemNum < InventorySlotNum; }

	void ShowInventoryItemToolTip(class UBaseItem * Item);
	void HideInventoryItemToolTip();
	void UpdateInventoryItemToolTip(class UBaseItem* Item);
	void UpdateEquipItemToolTip(class UBaseItem* Item);

protected:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//드래그가 감지되면 호출되는 함수
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
private:
	UFUNCTION()
	void ClickExitButton();	//나가기 버튼 클릭

private:
	//Slot
	//---------------------------------------------------
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	TArray<class UInventorySlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UInventorySlot> InventorySlotClass;

	const int InventorySlotNum = 20;
	int CurrentItemNum = 0;
	//---------------------------------------------------

	
	//ToolTip
	//---------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UItemToolTip> ItemToolTipWidgetClass;

	UPROPERTY()
	class UItemToolTip* EquipItemToolTip;		//장착한 아이템 툴팁

	UPROPERTY()
	class UItemToolTip* InventoryItemToolTip;	//인벤토리에 있는 아이템 툴팁
	//---------------------------------------------------


	UPROPERTY()
	class UButton* ExitButton;

	class AArcher* CurrentPlayer;

	FVector2D DragOffset;
};
