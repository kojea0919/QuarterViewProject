// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PurchaseQuantitySelector.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Misc/DefaultValueHelper.h"
#include "Item/BaseItem.h"
#include "Store.h"

void UPurchaseQuantitySelector::NativeConstruct()
{
	Super::NativeConstruct();

	QuantityEditTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("QuantityTextBox")));
	if (QuantityEditTextBox)
		QuantityEditTextBox->OnTextChanged.AddDynamic(this, &UPurchaseQuantitySelector::ChangeEditTextBox);

	IncreaseQuantitiyButton = Cast<UButton>(GetWidgetFromName(TEXT("QuantityUpButton")));
	if(IncreaseQuantitiyButton)
		IncreaseQuantitiyButton->OnClicked.AddDynamic(this, &UPurchaseQuantitySelector::ClickedIncreaseButton);

	DecreaseQuantitiyButton = Cast<UButton>(GetWidgetFromName(TEXT("QuantityDownButton")));
	if (DecreaseQuantitiyButton)
		DecreaseQuantitiyButton->OnClicked.AddDynamic(this, &UPurchaseQuantitySelector::ClickedDecreaseButton);

	PurchaseButton = Cast<UButton>(GetWidgetFromName(TEXT("PurchaseButton")));
	if (PurchaseButton)
		PurchaseButton->OnClicked.AddDynamic(this, &UPurchaseQuantitySelector::ClickedPurchaseButton);

	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));
	if (CancelButton)
		CancelButton->OnClicked.AddDynamic(this, &UPurchaseQuantitySelector::ClickedCancelButton);

	CurrentStore = nullptr;
	CurrentQuantity = 0;
}

void UPurchaseQuantitySelector::ChangeEditTextBox(const FText& Text)
{
	int PrevQuantity = CurrentQuantity;
	if (FDefaultValueHelper::ParseInt(Text.ToString(), CurrentQuantity))
	{
		if (CurrentQuantity > MaxQuantity)
		{
			CurrentQuantity = MaxQuantity;
			QuantityEditTextBox->SetText(FText::AsNumber(CurrentQuantity));
		}
	}
	else
	{
		QuantityEditTextBox->SetText(FText::AsNumber(PrevQuantity));
		CurrentQuantity = PrevQuantity;
	}
}

void UPurchaseQuantitySelector::ClickedIncreaseButton()
{
	++CurrentQuantity;
	if (CurrentQuantity > MaxQuantity)
		CurrentQuantity = MaxQuantity;

	if (QuantityEditTextBox)
		QuantityEditTextBox->SetText(FText::AsNumber(CurrentQuantity));
}

void UPurchaseQuantitySelector::ClickedDecreaseButton()
{
	--CurrentQuantity;
	if (CurrentQuantity < 0)
		CurrentQuantity = 0;

	if (QuantityEditTextBox)
		QuantityEditTextBox->SetText(FText::AsNumber(CurrentQuantity));
}

void UPurchaseQuantitySelector::ClickedCancelButton()
{
	SetVisibility(ESlateVisibility::Hidden);
	CurrentQuantity = 0;

	if(QuantityEditTextBox)
		QuantityEditTextBox->SetText(FText::AsNumber(CurrentQuantity));
}

void UPurchaseQuantitySelector::ClickedPurchaseButton()
{
	if (CurrentQuantity == 0)
		return;

	SetVisibility(ESlateVisibility::Hidden);

	if (CurrentStore)
		CurrentStore->AddPurchaseSlot(CurrentItemName,CurrentQuantity);

	CurrentQuantity = 0;
	if (QuantityEditTextBox)
		QuantityEditTextBox->SetText(FText::AsNumber(CurrentQuantity));

	CurrentItemName = TEXT("");
}
