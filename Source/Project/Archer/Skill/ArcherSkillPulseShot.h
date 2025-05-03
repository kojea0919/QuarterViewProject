// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/BaseSkill.h"
#include "ArcherSkillPulseShot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillPulseShot : public UBaseSkill
{
	GENERATED_BODY()

public:
	UArcherSkillPulseShot();

	virtual bool Use() override;
	
};
