// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "BossMeteorOverlapEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossMeteorOverlapEffect : public AParticleEffectActor
{
	GENERATED_BODY()
	
public:
	ABossMeteorOverlapEffect();

	virtual void OnParticleSystemFinished_Impl() override;

	virtual void SetEffectEnable(bool Enable) override;
private:
	UPROPERTY()
	class USoundCue* HitSound;

};
