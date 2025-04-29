// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equipment.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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

		int AttackStat = NewWeapon->GetAttackStat();
		int CriticalStat = NewWeapon->GetCriticalStat();

		AddAttackStat(AttackStat);
		AddCriticalStat(CriticalStat);

		WeaponAttackStat = AttackStat;
		WeaponCriticalStat = CriticalStat;
	}
}

void UEquipment::SetArmor(UArmorItem* NewArmor)
{
	UImage* TargetImage = nullptr;
	int ArmorStat = NewArmor->GetArmorStat();
	switch (NewArmor->GetArmorType())
	{
	case EArmorType::Hat:
		TargetImage = HatEquipImage;
		HatArmorStat = ArmorStat;
		HatIsEmpty = false;
		break;
	case EArmorType::Chest:
		TargetImage = ChestEquipImage;
		ChestArmorStat = ArmorStat;
		ChestIsEmpty = false;
		break;
	case EArmorType::Pants:
		TargetImage = PantsEquipImage;
		PantsArmorStat = ArmorStat;
		PantsIsEmpty = false;
		break;
	case EArmorType::Glove:
		TargetImage = GloveEquipImage;
		GloveArmorStat = ArmorStat;
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

	AddArmorStat(NewArmor->GetArmorStat());
	
}

void UEquipment::AddAttackStat(int Num)
{
	AddStatText(AttackStatText, Num);
}

void UEquipment::AddArmorStat(int Num)
{
	AddStatText(ArmorStatText, Num);
}

void UEquipment::AddCriticalStat(int Num)
{
	AddStatText(CriticalStatText, Num);
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

	
	//StatText
	//----------------------------------------------------------------------------
	AttackStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackStatText")));
	ArmorStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorStatText")));
	CriticalStatText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CriticalStatText")));
	//----------------------------------------------------------------------------

	WeaponAttackStat = 0;
	WeaponCriticalStat = 0;

	HatArmorStat = 0;
	ChestArmorStat = 0;
	PantsArmorStat = 0;
	GloveArmorStat = 0;
}

void UEquipment::AddStatText(UTextBlock* Text, int Stat)
{
	if (Text)
	{
		FText StatText = Text->GetText();
		int PrevStat = FCString::Atoi(*StatText.ToString());

		Text->SetText(FText::AsNumber(PrevStat + Stat));
	}
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
		AddArmorStat(-HatArmorStat);
		HatArmorStat = 0;

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
		AddArmorStat(-ChestArmorStat);
		ChestArmorStat = 0;

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
		AddArmorStat(-PantsArmorStat);
		PantsArmorStat = 0;

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
		AddArmorStat(-GloveArmorStat);
		GloveArmorStat = 0;

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
		AddAttackStat(-WeaponAttackStat);
		AddCriticalStat(-WeaponCriticalStat);

		CurrentPlayer->UnEquipWeapon();
		WeaponEquipImage->SetBrushFromTexture(nullptr);
		WeaponEquipImage->SetVisibility(ESlateVisibility::Hidden);

		WeaponIsEmpty = true;
	}
}
