// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSpecialAttackArrowEffect.h"
#include "NiagaraSystem.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcherSpecialAttackArrowEffect::AArcherSpecialAttackArrowEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_SpecialArrow.NS_Archer_SpecialArrow"));
}

void AArcherSpecialAttackArrowEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherSpecialAttackArrowEffect(this);
}
