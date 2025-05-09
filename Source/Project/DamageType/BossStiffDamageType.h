// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageType/BossDamageType.h"
#include "BossStiffDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossStiffDamageType : public UBossDamageType
{
	GENERATED_BODY()

public:
	UBossStiffDamageType()
		: UBossDamageType(EBossDamageType::Stiff)
	{}	
};
