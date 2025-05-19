// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubSystem/BossBattleSubSystem.h"
#include "GamePlayEffect/LevelSequence/PlayeLevelSequenceActor.h"
#include "GamePlayEffect/Sky/Sky.h"
#include "GamePlayEffect/Light/MainLevelLight.h"

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

void UBossBattleSubSystem::PlayBossPhase3Sequence()
{
	if (BossPhase3Sequence)
	{
		BossPhase3Sequence->PlayLevelSequence();
	}
}

void UBossBattleSubSystem::SetBurnSkyHidden()
{
	if (BurnSky)
		BurnSky->SetActorHiddenInGame(true);
}

void UBossBattleSubSystem::SetDeathSkyVisible()
{
	if (DeathSky)
		DeathSky->SetActorHiddenInGame(false);
}

void UBossBattleSubSystem::RecaptureSky()
{
	if (MainLevelLight)
		MainLevelLight->RecaptureSkyLight();
}

void UBossBattleSubSystem::SetDirectionalLigthIntensity(float Intensity)
{
	if (MainLevelLight)
		MainLevelLight->SetIntensityDirLight(Intensity);
}

void UBossBattleSubSystem::SetPhase2Light()
{
	SetBurnSkyHidden();
	SetDeathSkyVisible();
	RecaptureSky();
	SetDirectionalLigthIntensity(0.01f);
}

void UBossBattleSubSystem::ResetSky()
{
	if (BurnSky)
		BurnSky->SetActorHiddenInGame(false);
	if (DeathSky)
		DeathSky->SetActorHiddenInGame(true);
}

void UBossBattleSubSystem::ResetLight()
{
	if (MainLevelLight)
		MainLevelLight->RecaptureSkyLight();

	if (MainLevelLight)
		MainLevelLight->SetIntensityDirLight(6);
}
