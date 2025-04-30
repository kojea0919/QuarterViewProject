// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemStruct.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:
	UBaseItem();
	UBaseItem(EItemListType Type);

public:
	void SetTexture(UTexture2D* Texture) { ItemTexture = Texture; }
	UTexture2D* GetTexture() const { return ItemTexture; }

	//const FBaseItemInfoStruct& GetItemInfo() const { return *CurrentItemInfo; }
	const FBaseItemInfoStruct& GetItemInfo() const;

	EItemListType GetItemType() const { return ItemInfo.ItemType; }

	virtual int GetQuantity() const { return Quantity; }

	virtual void SetQuantity(int Num) { Quantity = Num; }

	int GetPrice() const { return ItemInfo.Price; }

	virtual class UBaseItem* GetCopyItem() const
	{
		return nullptr;
	}

	//const FString& GetItemName() const { return CurrentItemInfo->ItemName; }
	const FString& GetItemName() const;

	void SetTexturePath(const FString& Path) { TexturePath = Path; }

protected:
	UPROPERTY()
	UTexture2D* ItemTexture;

	FString TexturePath;

	FBaseItemInfoStruct ItemInfo;

	int Quantity = 1;			//아이템 개수

};
