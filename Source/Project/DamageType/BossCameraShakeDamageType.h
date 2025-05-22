// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageType/BossDamageType.h"
#include "BossCameraShakeDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossCameraShakeDamageType : public UBossDamageType
{
	GENERATED_BODY()

public:
	UBossCameraShakeDamageType()
		: UBossDamageType(EBossDamageType::CameraShake)
	{
	}
};
