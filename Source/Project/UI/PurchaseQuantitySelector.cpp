// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PurchaseQuantitySelector.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

void UPurchaseQuantitySelector::NativeConstruct()
{
	Super::NativeConstruct();

	QuantityEditTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("QuantityTextBox")));
	if (QuantityEditTextBox)
		QuantityEditTextBox->OnTextChanged.AddDynamic(this, &UPurchaseQuantitySelector::ChangeEditTextBox);

	IncreaseQuantitiyButton = Cast<UButton>(GetWidgetFromName(TEXT("QuantityUpButton")));

	DecreaseQuantitiyButton = Cast<UButton>(GetWidgetFromName(TEXT("QuantityDownButton")));

	PurchaseButton = Cast<UButton>(GetWidgetFromName(TEXT("PurchaseButton")));

	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));
}

void UPurchaseQuantitySelector::ChangeEditTextBox(const FText& Text)
{
	
}
