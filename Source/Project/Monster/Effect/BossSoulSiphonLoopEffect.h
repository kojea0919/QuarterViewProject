// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "BossSoulSiphonLoopEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossSoulSiphonLoopEffect : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	ABossSoulSiphonLoopEffect();

	virtual void OnParticleSystemFinished_Impl() override;
};
