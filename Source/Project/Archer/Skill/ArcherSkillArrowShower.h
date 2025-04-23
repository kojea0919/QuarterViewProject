// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/SkillBase/ChargingSkill/ChargingSkill.h"
#include "ArcherSkillArrowShower.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillArrowShower : public UChargingSkill
{
	GENERATED_BODY()

public:
	UArcherSkillArrowShower();

	virtual bool Use();

	virtual void ReleaseEffect();
	
};
