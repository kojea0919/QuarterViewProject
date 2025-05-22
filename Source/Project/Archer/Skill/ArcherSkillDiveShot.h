// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/BaseSkill.h"
#include "ArcherSkillDiveShot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillDiveShot : public UBaseSkill
{
	GENERATED_BODY()

public:
	UArcherSkillDiveShot();

public:
	virtual bool Use() override;

public:
	virtual void CheckEnemyOverlap() override;

};
