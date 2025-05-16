// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubSystem/BossBattleSubSystem.h"
#include "GamePlayEffect/LevelSequence/PlayeLevelSequenceActor.h"

void UBossBattleSubSystem::ResetSequence()
{
	BossSpawnSequence->ResetIsPlayed();
	BossPhase2Sequence->ResetIsPlayed();
}

void UBossBattleSubSystem::PlayBossPhase2Sequence()
{
	if (BossPhase2Sequence)
	{
		BossPhase2Sequence->PlayLevelSequence();
	}
}
