// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/ComboSkill/ComboSkill.h"
#include "ArcherSkillFlippingArrow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillFlippingArrow : public UComboSkill
{
	GENERATED_BODY()

public:
	UArcherSkillFlippingArrow();

	virtual bool Use();

};
