// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BossBattleSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossBattleSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void SaveBossTransform(const FTransform& Transform) { BossSavedTransform = Transform; }
	void SavePlayerTransform(const FTransform& Transform) { PlayerSavedTransform = Transform; }

	const FTransform& GetSaveBossTransform() const { return BossSavedTransform; }
	const FTransform& GetSavePlayerTransform() const { return PlayerSavedTransform; }

private:
	FTransform BossSavedTransform;
	FTransform PlayerSavedTransform;
};
