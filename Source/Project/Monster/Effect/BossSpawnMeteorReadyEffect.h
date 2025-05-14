// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "BossSpawnMeteorReadyEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossSpawnMeteorReadyEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	ABossSpawnMeteorReadyEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl() override;

	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

private:
	//장판 크기
	const float TelegraphRadius = 800.0f;

	//장판 LifeTime
	const float TelegraphRectangleLifeTime = 1.18;

	float Damage = 300.0f;
};
