// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemToolTip::SetItemToolTip(UTexture2D * ItemTexture, const FBaseItemInfoStruct& ItemInfo)
{
	if (ItemImage)
		ItemImage->SetBrushFromTexture(ItemTexture);

	if (ItemNameTextBlock)
		ItemNameTextBlock->SetText(FText::FromString(ItemInfo.ItemName));
	
	if (ItemDescriptionTextBlock)
		ItemDescriptionTextBlock->SetText(FText::FromString(ItemInfo.Description));

	if (ItemStatTextBlock)
		ItemStatTextBlock->SetText(FText::FromString(ItemInfo.GetItemStat()));
}

void UItemToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescriptionTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescription")));
	ItemStatTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemStat")));
}
