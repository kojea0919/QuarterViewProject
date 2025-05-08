// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/NiagaraEffectActor.h"
#include "BossDomainExpansionEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossDomainExpansionEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()

public:
	ABossDomainExpansionEffect();

public:
	virtual void OnNiagaraSystemFinished_Impl() override;

	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	//Scale Curve
	UPROPERTY()
	UCurveFloat* ScaleCurve;

	const float MaxTime = 3.0f;
	float CurTime;


};
