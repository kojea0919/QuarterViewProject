// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherBasicAttackArrowEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherBasicAttackArrowEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	AArcherBasicAttackArrowEffect();

public:
	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

	virtual void OnNiagaraSystemFinished_Impl();
};
