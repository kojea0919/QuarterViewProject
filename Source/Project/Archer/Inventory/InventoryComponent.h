// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

public:
	void SetInventory(class UInventory* Inven) { Inventory = Inven; }

	void AddItem(class UBaseItem* Item);

	bool IsCanAddItem();

protected:
	virtual void BeginPlay() override;


private:
	class UInventory* Inventory;
};
