// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemPurchaseSlot.h"
#include "Components/Image.h"
#include "Item/BaseItem.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Store.h"

void UItemPurchaseSlot::SetItem(const UBaseItem* Item)
{
	if (nullptr == Item)
		return;

	CurItem = Item;

	if (ItemImage)
	{
		ItemImage->SetBrushFromTexture(Item->GetTexture());
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
	CurItem = nullptr;

}

void UItemPurchaseSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));

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
