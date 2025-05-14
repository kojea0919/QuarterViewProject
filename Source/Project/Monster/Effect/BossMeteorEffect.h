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

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetOverlapEventOn();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* MeteorCollider;

	const float FallSpeed = 3000;

	//현재 이동 거리
	float CurMoveDistance;

	float MeteorDamage = 100.0f;
};
