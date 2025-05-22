// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "BossDamageType.generated.h"


enum class EBossDamageType
{
	Stiff,
	KnockBack,
	CameraShake
};

/**
 * 
 */
UCLASS()
class PROJECT_API UBossDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UBossDamageType()
	{
	}

	UBossDamageType(EBossDamageType Type)
		: CurDamageType(Type)
	{

	}

public:
	void SetDamageType(EBossDamageType Type) { CurDamageType = Type; }
	EBossDamageType GetDamageType() const { return CurDamageType; }

private:
	EBossDamageType CurDamageType;
};
