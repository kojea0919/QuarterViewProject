// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"

void UItemToolTip::SetItemToolTip(UTexture2D * ItemTexture, const FBaseItemInfoStruct& ItemInfo)
{
	if (ItemImage)
		ItemImage->SetBrushFromTexture(ItemTexture);

	if (ItemNameTextBlock)
		ItemNameTextBlock->SetText(FText::FromString(ItemInfo.ItemName));
	
	if (ItemDescriptionTextBlock)
		ItemDescriptionTextBlock->SetText(FText::FromString(ItemInfo.Description));

	if (ItemStatTextBlock)
	{
		switch (ItemInfo.ItemType)
		{
		case EItemListType::Weapon:
			ItemStatTextBlock->SetText(FText::FromString(ItemInfo.GetWeaponItemStat()));
			break;
		case EItemListType::Armor:
			ItemStatTextBlock->SetText(FText::FromString(ItemInfo.GetArmorItemStat()));
			break;
		case EItemListType::Potion:
			ItemStatTextBlock->SetText(FText::FromString(ItemInfo.GetPotionItemStat()));
			break;
		default:
			break;
		}
	}

	double X, Y;
	GetOwningPlayer()->GetMousePosition(X, Y);
	SetPositionInViewport(FVector2D(X, Y) + Offset);
}

void UItemToolTip::SetEquipTextOn()
{
	EquipText->SetVisibility(ESlateVisibility::Visible);
}

int UItemToolTip::GetHeight()
{
	if(SizeBox)
		return SizeBox->GetHeightOverride();
	return -1;
}

void UItemToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
	ItemNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemDescriptionTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDescription")));
	ItemStatTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemStat")));
	EquipText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EquipText")));
	if (EquipText)
		EquipText->SetVisibility(ESlateVisibility::Hidden);

	SizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("ToolTipSizeBox")));
}

void UItemToolTip::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	double X, Y;
	GetOwningPlayer()->GetMousePosition(X, Y);
	SetPositionInViewport(FVector2D(X, Y) + Offset);
}
