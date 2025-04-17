// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherBasicAttackMuzzleEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcherBasicAttackMuzzleEffect::AArcherBasicAttackMuzzleEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_BasicAttackMuzzle.NS_Archer_BasicAttackMuzzle"));
}

void AArcherBasicAttackMuzzleEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherBasicAttackMuzzleEffect(this);
}
