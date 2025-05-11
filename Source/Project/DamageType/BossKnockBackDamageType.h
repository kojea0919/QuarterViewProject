// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageType/BossDamageType.h"
#include "BossKnockBackDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossKnockBackDamageType : public UBossDamageType
{
	GENERATED_BODY()

public:
	UBossKnockBackDamageType()
		: UBossDamageType(EBossDamageType::KnockBack)
	{
	}
};
