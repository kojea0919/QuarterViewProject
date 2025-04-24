// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherSpecialAttackArrowEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherSpecialAttackArrowEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	AArcherSpecialAttackArrowEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl();
};
