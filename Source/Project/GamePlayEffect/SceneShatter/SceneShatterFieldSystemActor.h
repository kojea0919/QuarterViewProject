// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Field/FieldSystemActor.h"
#include "SceneShatterFieldSystemActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ASceneShatterFieldSystemActor : public AFieldSystemActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Explode();

};
