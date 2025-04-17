// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor.h"
#include "MeshEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMeshEffectActor : public ABaseEffectActor
{
	GENERATED_BODY()

public:
	AMeshEffectActor();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetEffectEnable(bool Enable) override;

private:
	virtual void LoadMaterial() {};
	
};
