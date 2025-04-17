// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherBasicAttackArrowEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcherBasicAttackArrowEffect::AArcherBasicAttackArrowEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_BasicAttackArrow.NS_Archer_BasicAttackArrow"));
}

void AArcherBasicAttackArrowEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	NiagaraComp->SetVariableFloat(TEXT("VelocitySpeed1"), 4000.0f);
}

void AArcherBasicAttackArrowEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherBasicAttackArrowEffect(this);
}