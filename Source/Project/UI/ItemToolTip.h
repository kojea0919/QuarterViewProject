// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemStruct.h"
#include "ItemToolTip.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UItemToolTip : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemToolTip(UTexture2D* ItemTexture, const FBaseItemInfoStruct& ItemInfo);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* ItemNameTextBlock;

	UPROPERTY()
	class UTextBlock* ItemDescriptionTextBlock;

	UPROPERTY()
	class UTextBlock* ItemStatTextBlock;
};
