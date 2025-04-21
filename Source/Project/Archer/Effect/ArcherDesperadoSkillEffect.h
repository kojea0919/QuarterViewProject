// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "ArcherDesperadoSkillEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherDesperadoSkillEffect : public ANiagaraEffectActor
{
	GENERATED_BODY()


public:
	AArcherDesperadoSkillEffect();

public:
	virtual void SpwanNiagaraEffect(const FTransform& Transform) override;

	virtual void OnNiagaraSystemFinished_Impl();

private:
	const FTransform Offset;
};
