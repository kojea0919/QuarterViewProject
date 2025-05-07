// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherBasicAttackMuzzleEffect.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "WorldSubSystem/EffectObjectPool.h"

AArcherBasicAttackMuzzleEffect::AArcherBasicAttackMuzzleEffect()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_MUZZLE(TEXT("/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_SparrowPrimaryMuzzleFlash.P_SparrowPrimaryMuzzleFlash"));
	if (PS_MUZZLE.Succeeded())
	{
		Effect->SetTemplate(PS_MUZZLE.Object);
	}

	Effect->SetWorldScale3D(FVector(3.5f));
}

void AArcherBasicAttackMuzzleEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherBasicAttackMuzzleEffect(this);
}
