// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Effect/ArcherPulseShotMuzzleEffect.h"
#include "NiagaraSystem.h"

AArcherPulseShotMuzzleEffect::AArcherPulseShotMuzzleEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Player/Archer/Effect/Niagara/NS_PulseShot_Muzzle.NS_PulseShot_Muzzle"));
}
