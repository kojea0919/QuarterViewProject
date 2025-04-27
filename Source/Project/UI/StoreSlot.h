// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStoreSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItemImage(UTexture2D* Texture);
	void SetItemNameText(FString ItemName);
	void SetItemPriceText(int ItemPrice);

	void SetHiddenItemImage();
	void SetHiddenItemNameText();
	void SetHiddenItemPrice();
	void SetHiddenGoldImage();

	void SetIsSetItem(bool IsSet) { IsSetItem = IsSet; }

	void SetItemInfo(const class UBaseItem* BaseItem) { Item = BaseItem; }

	void SetStore(class UStore* Store) { CurrentStore = Store; }

	UFUNCTION()
	void ShowDescription();

	UFUNCTION()
	void RemoveDescription();

	//구매 리스트에 현재 아이템 이미지를 추가
	UFUNCTION()
	void ClickedStoreSlot();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* ItemNameTextBlock;

	UPROPERTY()
	class UTextBlock* ItemPriceTextBlock;
	
	UPROPERTY()
	class UImage* GoldImage;

	UPROPERTY()
	class UButton* StoreSlotButton;

	bool IsSetItem;	//현재 슬롯에 아이템이 들어있는지 나타내는 변수

	const class UBaseItem* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemToolTip> ItemToolTipWidgetClass;

	class UItemToolTip* ToolTip;

	const FVector2D ToolTipOffset = { 5,0 };

	UTexture2D* ItemTexture;

	class UStore* CurrentStore;
};
