// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "ArcherDamageType.generated.h"

/**
 * 
 */

enum class EArcherDamageType
{
	Basic
};

UCLASS()
class PROJECT_API UArcherDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UArcherDamageType()
	{}

	UArcherDamageType(EArcherDamageType Type)
		: CurDamageType(Type)
	{

	}

public:
	void SetDamageType(EArcherDamageType Type) { CurDamageType = Type; }
	EArcherDamageType GetDamageType() const { return CurDamageType; }

private:
	EArcherDamageType CurDamageType;

};
