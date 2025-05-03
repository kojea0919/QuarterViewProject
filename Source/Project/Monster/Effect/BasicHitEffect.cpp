// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BasicHitEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "WorldSubSystem/EffectObjectPool.h"

ABasicHitEffect::ABasicHitEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/NS_BasicHit.NS_BasicHit"));
}

void ABasicHitEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);
}

void ABasicHitEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnBasicHitEffect(this);
}
