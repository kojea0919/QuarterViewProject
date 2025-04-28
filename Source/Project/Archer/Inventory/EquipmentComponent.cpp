// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Inventory/EquipmentComponent.h"
#include "UI/Equipment.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "Archer/Archer.h"

UEquipmentComponent::UEquipmentComponent()
	: EquipWidget(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEquipmentComponent::SetEquip(UEquipment* Equip)
{
	if (Equip)
	{
		EquipWidget = Equip;
		EquipWidget->SetPlayer(GetOwner<AArcher>());
	}
}

void UEquipmentComponent::EquipWeapon(UWeaponItem* WeaponItem)
{
	if (WeaponItem)
	{
		UWeaponItem* PrevItem = CurWeapon;
		CurWeapon = WeaponItem;

		if (EquipWidget)
			EquipWidget->SetWeapon(WeaponItem);

		//이전 아이템이 존재하면 원래 Inventory로 이동
		if (PrevItem)
		{
			AArcher* Archer = GetOwner<AArcher>();
			if (Archer)
			{
				Archer->AddItem(PrevItem);
			}
		}
	}
}

void UEquipmentComponent::EquipArmor(UArmorItem* ArmorItem)
{
	if (ArmorItem)
	{
		UArmorItem* TargetArmor = nullptr;
		switch (ArmorItem->GetArmorType())
		{
		case EArmorType::Hat:
			TargetArmor = CurHat;
			CurHat = ArmorItem;
			break;
		case EArmorType::Chest:
			TargetArmor = CurChest;
			CurChest = ArmorItem;
			break;
		case EArmorType::Pants:
			TargetArmor = CurPants;
			CurPants = ArmorItem;
			break;
		case EArmorType::Glove:
			TargetArmor = CurGlove;
			CurGlove = ArmorItem;
			break;
		default:
			break;
		}

		UArmorItem* PrevItem = TargetArmor;

		if (EquipWidget)
			EquipWidget->SetArmor(ArmorItem);

		//이전 아이템이 존재하면 원래 Inventory로 이동
		if (PrevItem)
		{
			AArcher* Archer = GetOwner<AArcher>();
			if (Archer)
			{
				Archer->AddItem(PrevItem);
			}
		}
	}
}

void UEquipmentComponent::UnEquipWeapon()
{
	AArcher* Archer = GetOwner<AArcher>();
	if (Archer)
	{
		Archer->AddItem(CurWeapon);

		CurWeapon = nullptr;
	}
}

void UEquipmentComponent::UnEquipHat()
{

	AArcher* Archer = GetOwner<AArcher>();
	if (Archer)
	{
		Archer->AddItem(CurHat);

		CurHat = nullptr;
	}
}

void UEquipmentComponent::UnEquipChest()
{
	AArcher* Archer = GetOwner<AArcher>();
	if (Archer)
	{
		Archer->AddItem(CurChest);

		CurChest = nullptr;
	}
}

void UEquipmentComponent::UnEquipPants()
{
	AArcher* Archer = GetOwner<AArcher>();
	if (Archer)
	{
		Archer->AddItem(CurPants);

		CurPants = nullptr;
	}
}

void UEquipmentComponent::UnEquipGlove()
{
	AArcher* Archer = GetOwner<AArcher>();
	if (Archer)
	{
		Archer->AddItem(CurGlove);

		CurGlove = nullptr;
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

