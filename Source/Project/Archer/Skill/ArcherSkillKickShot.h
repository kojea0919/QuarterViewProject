// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/BaseSkill.h"
#include "ArcherSkillKickShot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillKickShot : public UBaseSkill
{
	GENERATED_BODY()

public:
	UArcherSkillKickShot();

	virtual bool Use() override;

public:
	virtual void CheckEnemyOverlap() override;

};
