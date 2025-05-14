// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotKey.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetQuickSlotSkill(class UBaseSkill* Skill, ESkillQuickSlot SlotKey);

	void UseSkill(ESkillQuickSlot SlotKey);
	void ReleaseSkill(ESkillQuickSlot SlotKey);

public:
	class USkillGaugeBar* GetSkillGaugeBar() const { return SkillGaugeBar; }

	void SetVisibilityIntersectionKey(bool Enable);
	void SetVisibilityInventory();
	void SetVisibilityEquipment();
	void SetVisibilityStore();
	void SetVisibilityBossClear();
	void SetVisibilityBossHPBar(bool Enable);

	class UInventory* GetInventory() { return Inventory; }
	class UEquipment* GetEquipment() { return Equipment; }

	//드롭되면 호출되는 함수
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void SetupStoreUI(class AStoreNPC * Npc,class AArcher * Player);

	void SetBossMaxHP(float HP);
	void SetBossCurrentHP(float newHP);
	void InitBossHP();

	void SetPlayerCurrentHPRate(float Rate);

protected:
	virtual void NativeConstruct() override;

private:
	//QuickSlot배열
	UPROPERTY()
	TArray<class USkillQuickSlot*> SkillQuickSlotArr;

	UPROPERTY()
	class USkillGaugeBar* SkillGaugeBar;

	UPROPERTY()
	UUserWidget* IntersectionKey;

	UPROPERTY()
	class UInventory* Inventory;

	UPROPERTY()
	class UEquipment* Equipment;

	UPROPERTY()
	class UStore* Store;

	UPROPERTY()
	class UBossClear* BossClear;

	UPROPERTY()
	class UBossHPBar* BossHPBar;

	UPROPERTY()
	class UPlayerProgressBar* PlayerProgressBar;
};
