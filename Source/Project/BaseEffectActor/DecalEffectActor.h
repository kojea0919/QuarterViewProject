// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor.h"
#include "DecalEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ADecalEffectActor : public ABaseEffectActor
{
	GENERATED_BODY()

public:
	ADecalEffectActor();

	virtual void SetEffectEnable(bool Enable);

	virtual void PostInitializeComponents() override;

private:
	virtual void LoadMaterial() {};

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynMaterial;
};
