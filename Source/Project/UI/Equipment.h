// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UEquipment : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetWeapon(class UWeaponItem * NewWeapon);
	void SetArmor(class UArmorItem* NewArmor);

	void SetPlayer(class AArcher* Player) { CurrentPlayer = Player; }

	void AddAttackStat(int Stat);
	void AddArmorStat(int Stat);
	void AddCriticalStat(int Stat);

protected:
	virtual void NativeConstruct() override;

private:
	void AddStatText(class UTextBlock* Text, int Stat);

private:
	UFUNCTION()
	void ClickExit();

	UFUNCTION()
	void ClickHat();

	UFUNCTION()
	void ClickChest();

	UFUNCTION()
	void ClickPants();

	UFUNCTION()
	void ClickGlove();

	UFUNCTION()
	void ClickWeapon();

private:
	UPROPERTY()
	class UButton* ExitButton;

	//Hat
	//----------------------------
	UPROPERTY()
	class UButton* HeadEquipButton;
	
	UPROPERTY()
	class UImage* HatEquipImage;

	bool HatIsEmpty;

	int HatArmorStat;
	//----------------------------


	//Chest
	//----------------------------
	UPROPERTY()
	class UButton* ChestEquipButton;

	UPROPERTY()
	class UImage* ChestEquipImage;

	bool ChestIsEmpty;

	int ChestArmorStat;
	//----------------------------

	//Pants
	//----------------------------
	UPROPERTY()
	class UButton* PantsEquipButton;

	UPROPERTY()
	class UImage* PantsEquipImage;

	bool PantsIsEmpty;

	int PantsArmorStat;
	//----------------------------

	//Glove
	//----------------------------
	UPROPERTY()
	class UButton* GloveEquipButton;

	UPROPERTY()
	class UImage* GloveEquipImage;

	bool GloveIsEmpty;

	int GloveArmorStat;
	//----------------------------

	//Weapon
	//----------------------------
	UPROPERTY()
	class UButton* WeaponEquipButton;

	UPROPERTY()
	class UImage* WeaponEquipImage;

	bool WeaponIsEmpty;

	int WeaponAttackStat;
	int WeaponCriticalStat;
	//----------------------------

	//StatText
	//----------------------------
	UPROPERTY()
	class UTextBlock* AttackStatText;

	UPROPERTY()
	class UTextBlock* CriticalStatText;

	UPROPERTY()
	class UTextBlock* ArmorStatText;

	//----------------------------

	class AArcher* CurrentPlayer;
};
