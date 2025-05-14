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

	void SetPlayerSpawnTransform(const FTransform& Transform) { BossMapPlayerSpawnTransform = Transform; }
	const FTransform& GetPlayerSpawnTransform() const { return BossMapPlayerSpawnTransform; }

	void SetBossSpawnTransform(const FTransform& Transform) { BossMapBossSpawnTransform = Transform; }
	const FTransform& GetBossSpawnTransform() const { return BossMapBossSpawnTransform; }

private:
	FTransform BossSavedTransform;
	FTransform PlayerSavedTransform;

	FTransform BossMapPlayerSpawnTransform;
	FTransform BossMapBossSpawnTransform;
};
