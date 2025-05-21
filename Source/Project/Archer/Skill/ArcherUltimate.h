// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/BaseSkill.h"
#include "ArcherUltimate.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherUltimate : public UBaseSkill
{
	GENERATED_BODY()
	
public:
	UArcherUltimate();

	virtual bool Use() override;
	virtual void End() override;
};
