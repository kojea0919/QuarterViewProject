// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "BossMeteorEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossMeteorEffect : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	ABossMeteorEffect();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnParticleSystemFinished_Impl() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* MeteorCollider;

	const float FallSpeed = 2000;

	//현재 이동 거리
	float CurMoveDistance;
};
