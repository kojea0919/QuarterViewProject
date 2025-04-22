// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/SkillBase/BaseSkill.h"
#include "ArcherSkillKickShot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillKickShot : public UBaseSkill
{
	GENERATED_BODY()

public:
	virtual bool Use() override;
};
