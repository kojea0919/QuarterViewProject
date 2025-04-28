// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "Archer/Archer.h"

void UEquipment::SetWeapon(UWeaponItem* NewWeapon)
{
	if (WeaponEquipButton)
	{
		WeaponEquipImage->SetVisibility(ESlateVisibility::Visible);

		//텍스쳐 바꾸기
		WeaponEquipImage->SetBrushFromTexture(NewWeapon->GetTexture());
		WeaponIsEmpty = false;
	}
}

void UEquipment::SetArmor(UArmorItem* NewArmor)
{
	UImage* TargetImage = nullptr;
	switch (NewArmor->GetArmorType())
	{
	case EArmorType::Hat:
		TargetImage = HatEquipImage;
		HatIsEmpty = false;
		break;
	case EArmorType::Chest:
		TargetImage = ChestEquipImage;
		ChestIsEmpty = false;
		break;
	case EArmorType::Pants:
		TargetImage = PantsEquipImage;
		PantsIsEmpty = false;
		break;
	case EArmorType::Glove:
		TargetImage = GloveEquipImage;
		GloveIsEmpty = false;
		break;
	default:
		break;
	}

	if (nullptr == TargetImage)
		return;

	TargetImage->SetVisibility(ESlateVisibility::Visible);

	//텍스쳐 바꾸기
	TargetImage->SetBrushFromTexture(NewArmor->GetTexture());
	
}

void UEquipment::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	if (ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UEquipment::ClickExit);


	//Chest
	//----------------------------------------------------------------------------
	ChestEquipImage = Cast<UImage>(GetWidgetFromName(TEXT("ChestEquipImage")));
	if (ChestEquipImage)
		ChestEquipImage->SetVisibility(ESlateVisibility::Hidden);
	ChestEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("ChestEquipButton")));
	if (ChestEquipButton)
		ChestEquipButton->OnClicked.AddDynamic(this, &UEquipment::ClickChest);

	ChestIsEmpty = true;
	//----------------------------------------------------------------------------

	//Hat
	//----------------------------------------------------------------------------
	HatEquipImage = Cast<UImage>(GetWidgetFromName(TEXT("HatEquipImage")));
	if (HatEquipImage)
		HatEquipImage->SetVisibility(ESlateVisibility::Hidden);
	HeadEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("HeadEquipButton")));
	if (HeadEquipButton)
		HeadEquipButton->OnClicked.AddDynamic(this, &UEquipment::ClickHat);

	HatIsEmpty = true;
	//----------------------------------------------------------------------------

	//Pants
	//----------------------------------------------------------------------------
	PantsEquipImage = Cast<UImage>(GetWidgetFromName(TEXT("PantsEquipImage")));
	if (PantsEquipImage)
		PantsEquipImage->SetVisibility(ESlateVisibility::Hidden);
	PantsEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("PantsEquipButton")));
	if (PantsEquipButton)
		PantsEquipButton->OnClicked.AddDynamic(this, &UEquipment::ClickPants);

	PantsIsEmpty = true;
	//----------------------------------------------------------------------------

	//Glove
	//----------------------------------------------------------------------------
	GloveEquipImage = Cast<UImage>(GetWidgetFromName(TEXT("GloveEquipImage")));
	if (GloveEquipImage)
		GloveEquipImage->SetVisibility(ESlateVisibility::Hidden);
	GloveEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("GloveEquipButton")));
	if (GloveEquipButton)
		GloveEquipButton->OnClicked.AddDynamic(this, &UEquipment::ClickGlove);

	GloveIsEmpty = true;
	//----------------------------------------------------------------------------

	//Weapon
	//----------------------------------------------------------------------------
	WeaponEquipImage = Cast<UImage>(GetWidgetFromName(TEXT("WeaponEquipImage")));
	if (WeaponEquipImage)
		WeaponEquipImage->SetVisibility(ESlateVisibility::Hidden);
	WeaponEquipButton = Cast<UButton>(GetWidgetFromName(TEXT("WeaponEquipButton")));
	if (WeaponEquipButton)
		WeaponEquipButton->OnClicked.AddDynamic(this, &UEquipment::ClickWeapon);

	WeaponIsEmpty = true;
	//----------------------------------------------------------------------------
}

void UEquipment::ClickExit()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UEquipment::ClickHat()
{
	if (HatIsEmpty)
		return;

	if (CurrentPlayer && CurrentPlayer->IsCanAddItem())
	{
		CurrentPlayer->UnEquipHat();
		HatEquipImage->SetBrushFromTexture(nullptr);
		HatEquipImage->SetVisibility(ESlateVisibility::Hidden);

		HatIsEmpty = true;
	}
}

void UEquipment::ClickChest()
{
	if (ChestIsEmpty)
		return;

	if (CurrentPlayer && CurrentPlayer->IsCanAddItem())
	{
		CurrentPlayer->UnEquipChest();
		ChestEquipImage->SetBrushFromTexture(nullptr);
		ChestEquipImage->SetVisibility(ESlateVisibility::Hidden);

		ChestIsEmpty = true;
	}
}

void UEquipment::ClickPants()
{
	if (PantsIsEmpty)
		return;

	if (CurrentPlayer && CurrentPlayer->IsCanAddItem())
	{
		CurrentPlayer->UnEquipPants();
		PantsEquipImage->SetBrushFromTexture(nullptr);
		PantsEquipImage->SetVisibility(ESlateVisibility::Hidden);

		PantsIsEmpty = true;
	}
}

void UEquipment::ClickGlove()
{
	if (GloveIsEmpty)
		return;

	if (CurrentPlayer && CurrentPlayer->IsCanAddItem())
	{
		CurrentPlayer->UnEquipGlove();
		GloveEquipImage->SetBrushFromTexture(nullptr);
		GloveEquipImage->SetVisibility(ESlateVisibility::Hidden);

		GloveIsEmpty = true;
	}
}

void UEquipment::ClickWeapon()
{
	if (WeaponIsEmpty)
		return;

	if (CurrentPlayer && CurrentPlayer->IsCanAddItem())
	{
		CurrentPlayer->UnEquipWeapon();
		WeaponEquipImage->SetBrushFromTexture(nullptr);
		WeaponEquipImage->SetVisibility(ESlateVisibility::Hidden);

		WeaponIsEmpty = true;
	}
}
