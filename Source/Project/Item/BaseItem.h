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

public:
	void SetTexture(UTexture2D* Texture) { ItemTexture = Texture; }
	UTexture2D* GetTexture() const { return ItemTexture; }

	const FBaseItemInfoStruct& GetItemInfo() const { return *CurrentItemInfo; }

protected:
	UTexture2D* ItemTexture;

	FBaseItemInfoStruct* CurrentItemInfo;
};
