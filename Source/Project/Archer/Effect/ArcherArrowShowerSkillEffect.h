// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherArrowShowerSkillEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherArrowShowerSkillEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	AArcherArrowShowerSkillEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl();

};
