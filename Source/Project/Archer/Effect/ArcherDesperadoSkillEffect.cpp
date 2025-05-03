// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherDesperadoSkillEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "WorldSubSystem/EffectObjectPool.h"

AArcherDesperadoSkillEffect::AArcherDesperadoSkillEffect()
	: Offset(FVector(0.0, 0.0, 290.0f))
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Effect/Niagara/NS_Archer_Desperado.NS_Archer_Desperado"));
}

void AArcherDesperadoSkillEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform + Offset);
}

void AArcherDesperadoSkillEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnDesperadoSkillEffect(this);
}
