// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "ArcherBasicAttackMuzzleEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherBasicAttackMuzzleEffect : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	AArcherBasicAttackMuzzleEffect();

public:
	virtual void OnParticleSystemFinished_Impl();
};
