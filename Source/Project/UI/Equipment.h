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

protected:
	virtual void NativeConstruct() override;

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
	//----------------------------


	//Chest
	//----------------------------
	UPROPERTY()
	class UButton* ChestEquipButton;

	UPROPERTY()
	class UImage* ChestEquipImage;

	bool ChestIsEmpty;
	//----------------------------

	//Pants
	//----------------------------
	UPROPERTY()
	class UButton* PantsEquipButton;

	UPROPERTY()
	class UImage* PantsEquipImage;

	bool PantsIsEmpty;
	//----------------------------

	//Glove
	//----------------------------
	UPROPERTY()
	class UButton* GloveEquipButton;

	UPROPERTY()
	class UImage* GloveEquipImage;

	bool GloveIsEmpty;
	//----------------------------

	//Weapon
	//----------------------------
	UPROPERTY()
	class UButton* WeaponEquipButton;

	UPROPERTY()
	class UImage* WeaponEquipImage;

	bool WeaponIsEmpty;
	//----------------------------

	class AArcher* CurrentPlayer;
};
