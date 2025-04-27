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
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ChangeEditTextBox(const FText & Text);

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
};
