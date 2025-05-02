// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "BasicHitEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABasicHitEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	ABasicHitEffect();

public:
	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

	virtual void OnNiagaraSystemFinished_Impl();

};
