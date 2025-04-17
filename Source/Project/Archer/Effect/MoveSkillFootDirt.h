// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "MoveSkillFootDirt.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMoveSkillFootDirt : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	AMoveSkillFootDirt();

public:
	virtual void OnNiagaraSystemFinished_Impl();
};
