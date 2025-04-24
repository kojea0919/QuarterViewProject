// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Store.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStore : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitStore();

	UFUNCTION()
	void ClickExit();

	UFUNCTION()
	void ClickDragDrop();

protected:
	virtual void NativeConstruct() override;


private:
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	class UButton* ExitButton;

	UPROPERTY()
	class UButton* DragDropBarButton;

	UPROPERTY()
	TArray<class UStoreSlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UStoreSlot> StoreSlotClass;

	const int StoreSlotNum = 8;
};
