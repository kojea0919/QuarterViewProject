// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubSystem/BossBattleSubSystem.h"
#include "GamePlayEffect/LevelSequence/PlayeLevelSequenceActor.h"

void UBossBattleSubSystem::ResetSequence()
{
	BossSpawnSequence->ResetIsPlayed();
}
