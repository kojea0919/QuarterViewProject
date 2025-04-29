// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemPurchaseSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/BaseItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Store.h"

void UItemPurchaseSlot::SetPotionItem(UTexture2D * Texture,int Quantity, const FString & ItemName)
{
	CurrentQuantity = Quantity;
	CurrentItemName = ItemName;

	if (ItemImage && nullptr != Texture)
	{
		ItemImage->SetBrushFromTexture(Texture);
		
		//포션인 경우에만 개수 Text 보여주기
		if (QuantityText)
		{
			QuantityText->SetVisibility(ESlateVisibility::Visible);
			QuantityText->SetText(FText::AsNumber(Quantity));
		}
		else
		{
			QuantityText->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UItemPurchaseSlot::SetEquipItem(UTexture2D* Texture,const FString & ItemName)
{
	CurrentItemName = ItemName;

	if (ItemImage && nullptr != Texture)
	{
		ItemImage->SetBrushFromTexture(Texture);

		if(QuantityText)
			QuantityText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UItemPurchaseSlot::SetImage(UTexture2D* Texture)
{
	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(Texture);
	}
}

void UItemPurchaseSlot::ClearSlot()
{
	ItemImage->SetBrushFromTexture(BaseTexture);
	QuantityText->SetVisibility(ESlateVisibility::Hidden);
	CurrentQuantity = 0;
	CurrentItemName = TEXT("");
}

int UItemPurchaseSlot::GetQuantity() const
{
	return CurrentQuantity;
}

void UItemPurchaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	QuantityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("QuantityText")));
	if(QuantityText)
		QuantityText->SetVisibility(ESlateVisibility::Hidden);

	BaseTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Player/UI/UITexture/TX_InventoryBackGroundImage.TX_InventoryBackGroundImage"));
}

FReply UItemPurchaseSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 왼쪽 마우스 버튼이 눌리면 현재 슬롯 비워주기
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		ItemImage->SetBrushFromTexture(BaseTexture);

		//Store UI에서 뒤에 슬롯 이미지를 앞으로 이동
		CurrentStore->UpdatePurchaseSlot(CurSlotIdx);
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
