// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "InventorySlot.h"
#include "Item/BaseItem.h"
#include "Archer/Archer.h"

void UInventory::InitInventory()
{
	for (size_t i = 0; i < InventorySlotNum; ++i)
	{
		UInventorySlot * InventorySlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
		InventorySlot->SetInventory(this);
		SlotArr.Push(InventorySlot);
		WrapBox->AddChild(InventorySlot);
	}
	CurrentItemNum = 0;
}

void UInventory::AddItem(UBaseItem* Item)
{
	if (CurrentItemNum == InventorySlotNum)
		return;

	//포션인 경우에는 같은 이름의 아이템이 있으면 개수 추가
	//-------------------------------------------------------
	int FristEmptySlotIdx = 0;
	bool FindEmptySlotIdx = false;
	if (Item->GetItemType() == EItemListType::Potion)
	{
		for (size_t i = 0; i < InventorySlotNum; ++i)
		{
			if (SlotArr[i]->IsEmpty() && !FindEmptySlotIdx)
			{
				FristEmptySlotIdx = i;
				FindEmptySlotIdx = true;
			}

			//같은 이름의 아이템이 있으면 개수를 최대한 추가해주고
			//남은 아이템은 새로운 슬롯에 추가
			if (SlotArr[i]->GetItemName() == Item->GetItemName())
			{
				int OriginQuantity = SlotArr[i]->GetQuantity();
				int NewQuantity = Item->GetQuantity();

				int AddQuantity = OriginQuantity + NewQuantity;
				if (AddQuantity > 99)
				{
					SlotArr[i]->SetQuantity(99);
					Item->SetQuantity(AddQuantity - 99);
				}
				else
				{
					SlotArr[i]->SetQuantity(AddQuantity);
					return;
				}
			}
		}
		++CurrentItemNum;
		SlotArr[FristEmptySlotIdx]->SetItem(Item);
		return;
	}
	//-------------------------------------------------------

	else
	{
		for (size_t i = 0; i < InventorySlotNum; ++i)
		{
			if (SlotArr[i]->IsEmpty())
			{
				++CurrentItemNum;
				SlotArr[i]->SetItem(Item);
				return;
			}
		}
	}
}

void UInventory::EquipItem(UBaseItem* Item)
{
	if (CurrentPlayer)
	{
		--CurrentItemNum;
		CurrentPlayer->EquipItem(Item);
	}
}

void UInventory::NativeConstruct()
{
	Super::NativeConstruct();

	WrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox")));

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	if (ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UInventory::ClickExitButton);

}

void UInventory::ClickExitButton()
{
	SetVisibility(ESlateVisibility::Hidden);
}
