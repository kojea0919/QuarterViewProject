// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "BossBigSwingAreaMarkEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossBigSwingAreaMarkEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()
	
public:
	ABossBigSwingAreaMarkEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl() override;

	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

private:
	//장판 크기
	const float TelegraphRadius = 700.0f;

	//장판 LifeTime
	const float TelegraphLifeTime = 0.45f;

	//장판 각도
	const float TelegraphAngle = 180.f;

};
