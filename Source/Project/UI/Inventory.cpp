// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Components/WrapBox.h"
#include "InventorySlot.h"

void UInventory::InitInventory()
{
	for (size_t i = 0; i < InventorySlotNum; ++i)
	{
		UInventorySlot * InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
		SlotArr.Push(InventorySlot);
		WrapBox->AddChild(InventorySlot);
	}
}

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	WrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox")));
}
