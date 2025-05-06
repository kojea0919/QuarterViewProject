// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossSpawnMeteorReadyEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

ABossSpawnMeteorReadyEffect::ABossSpawnMeteorReadyEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Circle.FX_Telegrap_Circle"));
}

void ABossSpawnMeteorReadyEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturntBossSpawnMeteorReadyEffect(this);
}

void ABossSpawnMeteorReadyEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	if (NiagaraComp)
	{
		NiagaraComp->SetVariableFloat(FName("User.Scale"), TelegraphRadius);
		NiagaraComp->SetVariableFloat(FName("User.LifeTime"), TelegraphRectangleLifeTime);
	}
}
