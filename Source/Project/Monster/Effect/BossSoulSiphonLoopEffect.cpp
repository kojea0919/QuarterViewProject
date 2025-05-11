// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossSoulSiphonLoopEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystemComponent.h"

ABossSoulSiphonLoopEffect::ABossSoulSiphonLoopEffect()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_SOULSIPHONLOOP(TEXT("/Game/ParagonSevarog/FX/Particles/Abilities/SoulSiphon/FX/P_SiphonTargeting.P_SiphonTargeting"));
	if (PS_SOULSIPHONLOOP.Succeeded())
	{
		Effect->SetTemplate(PS_SOULSIPHONLOOP.Object);
	}
}

void ABossSoulSiphonLoopEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnBossSoulSiphonLoopEffect(this);
}
