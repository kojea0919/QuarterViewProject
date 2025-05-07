// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "BossStoneSpikeAreaMarkEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossStoneSpikeAreaMarkEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	

public:
	ABossStoneSpikeAreaMarkEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl() override;

	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

private:
	//장판 크기
	const float TelegraphRadius = 1400.0f;

	//장판 LifeTime
	const float TelegraphLifeTime = 0.9f;

	//장판 각도
	const float TelegraphAngle = 40.f;

};
