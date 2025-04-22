// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherBigArrowEffect.h"
#include "NiagaraSystem.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcherBigArrowEffect::AArcherBigArrowEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_BigArrow.NS_Archer_BigArrow"));
}

void AArcherBigArrowEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherBigArrowEffect(this);
}
