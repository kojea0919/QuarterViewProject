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


protected:
	virtual void NativeConstruct() override;

private:
	//QuickSlot¹è¿­
	UPROPERTY()
	TArray<class USkillQuickSlot*> SkillQuickSlotArr;

};
