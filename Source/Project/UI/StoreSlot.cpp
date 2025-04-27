// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StoreSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ItemToolTip.h"
#include "Store.h"
#include "Item/ItemStruct.h"
#include "Item/BaseItem.h"

void UStoreSlot::SetItemImage(UTexture2D* Texture)
{
	if (ItemImage)
	{
		ItemTexture = Texture;
		ItemImage->SetBrushFromTexture(Texture);
		ItemImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreSlot::SetItemNameText(FString ItemName)
{
	if (ItemNameTextBlock)
	{
		ItemNameTextBlock->SetText(FText::FromString(ItemName));
		ItemNameTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreSlot::SetItemPriceText(int ItemPrice)
{
	if (ItemPriceTextBlock)
	{
		ItemPriceTextBlock->SetText(FText::AsNumber(ItemPrice));
		ItemPriceTextBlock->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreSlot::SetHiddenItemImage()
{
	if(ItemImage)
		ItemImage->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreSlot::SetHiddenItemNameText()
{
	if (ItemNameTextBlock)
		ItemNameTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreSlot::SetHiddenItemPrice()
{
	if (ItemPriceTextBlock)
		ItemPriceTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreSlot::SetHiddenGoldImage()
{
	if (GoldImage)
		GoldImage->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreSlot::ShowDescription()
{
	//아이템이 세팅돼 있으면 해당 아이템의 ToolTip을 생성
	if (IsSetItem)
	{
		ToolTip->SetItemToolTip(ItemTexture, Item->GetItemInfo());
		ToolTip->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreSlot::RemoveDescription()
{
	ToolTip->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreSlot::AddPurchaseWaitingList()
{
	if (CurrentStore && IsSetItem)
	{
		CurrentStore->SetPurchaseSlot(Item);
	}
}

void UStoreSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemTexture = nullptr;
	IsSetItem = false;

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemPriceTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemPrice")));
	GoldImage = Cast<UImage>(GetWidgetFromName(TEXT("GoldImage")));
	
	StoreSlotButton = Cast<UButton>(GetWidgetFromName(TEXT("StoreSlotButton")));
	if (StoreSlotButton)
	{
		StoreSlotButton->OnHovered.AddDynamic(this, &UStoreSlot::ShowDescription);
		StoreSlotButton->OnUnhovered.AddDynamic(this, &UStoreSlot::RemoveDescription);
		StoreSlotButton->OnClicked.AddDynamic(this, &UStoreSlot::AddPurchaseWaitingList);
	}

	ToolTip = CreateWidget<UItemToolTip>(GetWorld(), ItemToolTipWidgetClass);
	if (ToolTip)
	{
		ToolTip->AddToViewport(1);
		ToolTip->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UStoreSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ToolTip && ToolTip->IsVisible())
	{
		double X, Y;
		GetOwningPlayer()->GetMousePosition(X, Y);
		ToolTip->SetPositionInViewport(FVector2D(X, Y) + ToolTipOffset);
	}
}
