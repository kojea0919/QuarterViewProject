// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherArrowShowerSkillEffect.h"
#include "NiagaraSystem.h"
#include "WorldSubSystem/EffectObjectPool.h"

AArcherArrowShowerSkillEffect::AArcherArrowShowerSkillEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_ArrowShower.NS_Archer_ArrowShower'"));
}

void AArcherArrowShowerSkillEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherArrowShowerSkillEffect(this);
}
