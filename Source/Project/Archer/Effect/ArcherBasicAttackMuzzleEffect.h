// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherBasicAttackMuzzleEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherBasicAttackMuzzleEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()

public:
	AArcherBasicAttackMuzzleEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl();
};
