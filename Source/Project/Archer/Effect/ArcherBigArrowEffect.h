// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherBigArrowEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherBigArrowEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()

public:
	AArcherBigArrowEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl();
	

};
