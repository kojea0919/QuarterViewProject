// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPurchaseSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UItemPurchaseSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItem(const class UBaseItem* Item, int Quantity = 1);
	void SetImage(UTexture2D * Texture);
	void SetSlotIdx(int Idx) { CurSlotIdx = Idx; }
	void ClearSlot();

	void SetStore(class UStore* Store) { CurrentStore = Store; }

	const class UBaseItem* GetItem() const { return CurItem; }

	int GetQuantity() const { return CurrentQuantity; }
protected:
	virtual void NativeConstruct() override;

	//슬롯에 마우스 버튼이 눌리면 호출되는 함수
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UPROPERTY()
	class UImage* ItemImage;

	UPROPERTY()
	class UTextBlock* QuantityText;

	const class UBaseItem* CurItem;

	UTexture2D* BaseTexture;

	int CurSlotIdx;

	class UStore* CurrentStore;

	int CurrentQuantity;
};
