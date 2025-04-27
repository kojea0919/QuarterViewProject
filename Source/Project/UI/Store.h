// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreSlot.h"
#include "Item/ItemStruct.h"
#include "Store.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStore : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void InitStore();

	UFUNCTION()
	void ClickExit();

	UFUNCTION()
	void ClickWeapon();

	UFUNCTION()
	void ClickArmor();

	UFUNCTION()
	void ClickPotion();

	//Idx+1 부터 PurchaseSlotIdx까지 앞으로 한칸 씩 이동
	void UpdatePurchaseSlot(int Idx);

public:
	void SetStoreNPC(class AStoreNPC* Npc) { CurrentNPC = Npc; }
	void SetItemSlot();

	void ClickedStoreSlot(const class UBaseItem * Item);		//StoreSlot이 클릭되면 호출될 함수 Item은 클릭된 아이템

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//드래그가 감지되면 호출되는 함수
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

private:
	template<typename T>
	void SetItemSlot(const TArray<T*>& ItemArr);

private:
	//Slot
	//-----------------------------------------------
	UPROPERTY()
	class UWrapBox* WrapBox;

	UPROPERTY()
	TArray<class UStoreSlot*> SlotArr;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UStoreSlot> StoreSlotClass;

	const int StoreSlotNum = 6;
			
	FVector2D DragOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UStoreWidgetDrag> StoreWidgetDragClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UStoreDragWidget> StoreDragWidgetClass;
	//-----------------------------------------------

	//버튼 종류
	//-----------------------------------------------
	UPROPERTY()
	class UButton* ExitButton;			//종료 버튼

	UPROPERTY()
	class UButton* WeaponButton;		//무기 아이템 리스트 버튼

	UPROPERTY()
	class UButton* ArmorButton;			//방어구 아이템 리스트 버튼

	UPROPERTY()
	class UButton* PotionButton;			//포션 아이템 리스트 버튼
	//-----------------------------------------------

	//Item 구매 대기 Slot
	//-----------------------------------------------
	UPROPERTY()
	class UWrapBox* ItemPurchaseWaitingWrapBox;

	UPROPERTY()
	TArray<class UItemPurchaseSlot*> PurchaseSlotArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UItemPurchaseSlot> ItemPurchaseSlotClass;

	const int PurchaseSlotNum = 5;
	int PurchaseSlotIdx = 0;
	//-----------------------------------------------

	//Item 개수 선택 UI
	//-----------------------------------------------
	UPROPERTY()
	class UPurchaseQuantitySelector* PurchaseQuantitySelector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPurchaseQuantitySelector> PurchaseQuantitySelectorClass;
	//-----------------------------------------------

	class AStoreNPC* CurrentNPC;	//현재 아이템을 팔 NPC

	EItemListType CurrentItemButtonType;
};

template<typename T>
inline void UStore::SetItemSlot(const TArray<T*>& ItemArr)
{
	size_t ItemNum = ItemArr.Num();
	for (size_t i = 0; i < ItemNum; ++i)
	{
		UTexture2D* ItemTexture =  ItemArr[i]->GetTexture();
		const FBaseItemInfoStruct& ItemInfo = ItemArr[i]->GetItemInfo();

		SlotArr[i]->SetItemImage(ItemTexture);
		SlotArr[i]->SetItemNameText(ItemInfo.ItemName);
		SlotArr[i]->SetItemPriceText(ItemInfo.Price);
		SlotArr[i]->SetItemInfo(ItemArr[i]);
		SlotArr[i]->SetIsSetItem(true);
	}

	for (size_t i = ItemNum; i < StoreSlotNum; ++i)
	{
		SlotArr[i]->SetHiddenItemImage();
		SlotArr[i]->SetHiddenGoldImage();
		SlotArr[i]->SetHiddenItemNameText();
		SlotArr[i]->SetHiddenItemPrice();
		SlotArr[i]->SetIsSetItem(false);
	}
}
