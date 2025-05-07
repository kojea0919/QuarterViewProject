// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossStoneSpikeAreaMarkEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

ABossStoneSpikeAreaMarkEffect::ABossStoneSpikeAreaMarkEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Circle.FX_Telegrap_Circle"));
}

void ABossStoneSpikeAreaMarkEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnBossStoneSpikeAreaMarkEffect(this);
}

void ABossStoneSpikeAreaMarkEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	if (NiagaraComp)
	{
		NiagaraComp->SetVariableFloat(FName("User.Scale"), TelegraphRadius);
		NiagaraComp->SetVariableFloat(FName("User.LifeTime"), TelegraphLifeTime);
		NiagaraComp->SetVariableFloat(FName("User.CircleAngle"), TelegraphAngle);
	}
}
