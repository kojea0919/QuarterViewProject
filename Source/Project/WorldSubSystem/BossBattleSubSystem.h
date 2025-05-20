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

	void SetPlayerRespawnTransform(const FTransform& Transform) { PlayerRespawnTransform = Transform; }
	const FTransform& GetPlayerRespawnTransform() const { return PlayerRespawnTransform; }

	void ResetSequence();
	void SetBossSpawnSequence(class APlayeLevelSequenceActor* Sequence) { BossSpawnSequence = Sequence; }
	void SetBossPhase2Sequence(class APlayeLevelSequenceActor* Sequence) { BossPhase2Sequence = Sequence; }
	void SetBossPhase3Sequence(class APlayeLevelSequenceActor* Sequence) { BossPhase3Sequence = Sequence; }
	void SetBossDeadSequence(class APlayeLevelSequenceActor* Sequence) { BossDeadSequence = Sequence; }
	void PlayBossPhase2Sequence();
	void PlayBossPhase3Sequence();
	void PlayBossDeadSequence();

	void SetBurnSky(class ASky* Sky) { BurnSky = Sky; }
	void SetDeathSky(class ASky* Sky) { DeathSky = Sky; }

	void SetBurnSkyHidden();
	void SetDeathSkyVisible();

	void SetMainLevelLight(class AMainLevelLight* Light) { MainLevelLight = Light; }
	void RecaptureSky();
	void SetDirectionalLigthIntensity(float Intensity);

	void SetPhase2Light();
	
	void ResetSky();
	void ResetLight();

	void SetPhase3BossTransform(const FTransform& Trasnform) { Phase3BossTransform = Trasnform; }
	void SetPhase3PlayerTransform(const FTransform& Trasnform) { Phase3PlayerTransform = Trasnform; }

	const FTransform& GetPhase3BossTransform() const { return Phase3BossTransform; }
	const FTransform& GetPhase3PlayerTransform() const { return Phase3PlayerTransform; }

private:
	FTransform BossSavedTransform;
	FTransform PlayerSavedTransform;

	FTransform BossMapPlayerSpawnTransform;
	FTransform BossMapBossSpawnTransform;

	FTransform PlayerRespawnTransform;

	class APlayeLevelSequenceActor* BossSpawnSequence;
	class APlayeLevelSequenceActor* BossPhase2Sequence;
	class APlayeLevelSequenceActor* BossPhase3Sequence;
	class APlayeLevelSequenceActor* BossDeadSequence;

	class ASky* BurnSky;
	class ASky* DeathSky;
	
	class AMainLevelLight* MainLevelLight;

	FTransform Phase3BossTransform;
	FTransform Phase3PlayerTransform;

};
