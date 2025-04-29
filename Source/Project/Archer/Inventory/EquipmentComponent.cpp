// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Inventory/EquipmentComponent.h"
#include "UI/Equipment.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "Archer/Archer.h"

UEquipmentComponent::UEquipmentComponent()
	: EquipWidget(nullptr), CurWeapon(nullptr), CurHat(nullptr),
	CurChest(nullptr), CurPants(nullptr), CurGlove(nullptr)
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

UBaseItem* UEquipmentComponent::EquipWeapon(UWeaponItem* WeaponItem)
{
	UWeaponItem* PrevItem = nullptr;
	if (WeaponItem)
	{
		PrevItem = CurWeapon;
		CurWeapon = WeaponItem;

		if (EquipWidget)
		{
			EquipWidget->SetWeapon(WeaponItem);
			if (PrevItem)
			{
				EquipWidget->AddAttackStat(-PrevItem->GetAttackStat());
				EquipWidget->AddCriticalStat(-PrevItem->GetCriticalStat());
			}
		}
	}
	return PrevItem;
}

UBaseItem* UEquipmentComponent::EquipArmor(UArmorItem* ArmorItem)
{
	UArmorItem* PrevItem = nullptr;
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

		PrevItem = TargetArmor;

		if (EquipWidget)
		{
			EquipWidget->SetArmor(ArmorItem);

			if (PrevItem)
			{
				EquipWidget->AddArmorStat(-PrevItem->GetArmorStat());
			}
		}

	}
	return PrevItem;
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

const UBaseItem* UEquipmentComponent::GetWeapon() const
{
	 return CurWeapon;
}

const UBaseItem* UEquipmentComponent::GetArmor(EArmorType ArmorType) const
{
	switch (ArmorType)
	{
	case EArmorType::Hat:
		return CurHat;
	case EArmorType::Chest:
		return CurChest;
	case EArmorType::Pants:
		return CurPants;
	case EArmorType::Glove:
		return CurGlove;
	default:
		return nullptr;
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

