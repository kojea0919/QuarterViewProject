// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSkillFootDirt.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AMoveSkillFootDirt::AMoveSkillFootDirt()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_Archer_MoveSkillFootDirt.NS_Archer_MoveSkillFootDirt"));
}

void AMoveSkillFootDirt::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnMoveSkillFootDirt(this);
}
