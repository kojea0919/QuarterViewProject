// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Inventory/InventoryComponent.h"
#include "UI/Inventory.h"
#include "Archer/Archer.h"

UInventoryComponent::UInventoryComponent()
	: Inventory(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::AddItem(UBaseItem* Item)
{
	if (Inventory && Item)
	{
		Inventory->AddItem(Item);
		Inventory->SetPlayer(GetOwner<AArcher>());
	}
}

bool UInventoryComponent::IsCanAddItem()
{
	if (Inventory)
		return Inventory->IsCanAdd();
	return false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

