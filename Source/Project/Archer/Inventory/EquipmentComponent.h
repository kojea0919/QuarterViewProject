// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemStruct.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();

public:
	void SetEquip(class UEquipment* Equip);

	class UBaseItem* EquipWeapon(class UWeaponItem* WeaponItem);
	class UBaseItem* EquipArmor(class UArmorItem* WeaponItem);

	void UnEquipWeapon();
	void UnEquipHat();
	void UnEquipChest();
	void UnEquipPants();
	void UnEquipGlove();
	
	const class UBaseItem* GetWeapon() const;
	const class UBaseItem* GetArmor(EArmorType ArmorType) const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class UEquipment* EquipWidget;

	//ÀåÂøÁßÀÎ ¹«±â
	class UWeaponItem* CurWeapon;

	//ÀåÂøÁßÀÎ ¸ðÀÚ
	class UArmorItem* CurHat;

	//ÀåÂøÁßÀÎ °©¿Ê
	class UArmorItem* CurChest;

	//ÀåÂøÁßÀÎ ¹ÙÁö
	class UArmorItem* CurPants;

	//ÀåÂøÁßÀÎ Àå°©
	class UArmorItem* CurGlove;
		
};
