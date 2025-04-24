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

protected:
	virtual void NativeConstruct() override;

private:
	void ClickExit();


private:
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	class UButton* ExitButton;

	UPROPERTY()
	TArray<class UStoreSlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UStoreSlot> StoreSlotClass;

	const int StoreSlotNum = 8;
};
