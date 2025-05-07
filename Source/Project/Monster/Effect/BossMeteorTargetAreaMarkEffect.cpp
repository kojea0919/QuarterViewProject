// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossMeteorTargetAreaMarkEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Monster/Effect/BossMeteorEffect.h"

ABossMeteorTargetAreaMarkEffect::ABossMeteorTargetAreaMarkEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Circle.FX_Telegrap_Circle"));
}

void ABossMeteorTargetAreaMarkEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturntBossMeteorTargetAreaMarkEffect(this);
	
	ABossMeteorEffect * Meteor = EffectObjPool->GetBossMeteorEffect();
	Meteor->SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 1600.0f));
	Meteor->SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
	Meteor->SetOverlapEventOn();
}

void ABossMeteorTargetAreaMarkEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	if (NiagaraComp)
	{
		NiagaraComp->SetVariableFloat(FName("User.Scale"), TelegraphRadius);
		NiagaraComp->SetVariableFloat(FName("User.LifeTime"), TelegraphRectangleLifeTime);
		NiagaraComp->SetVariableFloat(FName("User.CircleAngle"), 360);
	}
}
