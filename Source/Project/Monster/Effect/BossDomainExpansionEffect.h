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

	virtual void SetEffectEnable(bool Enable);

public:
	virtual void Tick(float DeltaTime) override;

	void SetReverse() { IsReverse = true; }

private:
	//Scale Curve
	UPROPERTY()
	UCurveFloat* ScaleCurve;

	const float MaxTime = 10;
	float CurTime;

	bool IsReverse = false;

};
