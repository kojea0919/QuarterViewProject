// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PurchaseQuantitySelector.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPurchaseQuantitySelector : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetStore(class UStore* Store) { CurrentStore = Store; }
	void SetItem(const class UBaseItem* Item) { CurrentItem = Item; }

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ChangeEditTextBox(const FText & Text);

	UFUNCTION()
	void ClickedIncreaseButton();

	UFUNCTION()
	void ClickedDecreaseButton();

	UFUNCTION()
	void ClickedCancelButton();

	UFUNCTION()
	void ClickedPurchaseButton();

private:
	UPROPERTY()
	class UEditableTextBox* QuantityEditTextBox;

	UPROPERTY()
	class UButton* IncreaseQuantitiyButton;

	UPROPERTY()
	class UButton* DecreaseQuantitiyButton;

	UPROPERTY()
	class UButton* PurchaseButton;

	UPROPERTY()
	class UButton* CancelButton;

	int CurrentQuantity;		//현재 입력 받은 개수
	const int MaxQuantity = 99;

	class UStore* CurrentStore;

	const class UBaseItem* CurrentItem;
};
