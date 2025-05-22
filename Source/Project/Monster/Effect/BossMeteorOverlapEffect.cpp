// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossMeteorOverlapEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ABossMeteorOverlapEffect::ABossMeteorOverlapEffect()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_METEOROVERLAP(TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/ProjectileMeteor/FX/P_Gideon_RMB_HitWorld.P_Gideon_RMB_HitWorld"));
	if (PS_METEOROVERLAP.Succeeded())
	{
		Effect->SetTemplate(PS_METEOROVERLAP.Object);
	}

	Effect->SetWorldScale3D(FVector(0.5f));


	static ConstructorHelpers::FObjectFinder<USoundCue> SC_HITSOUND(TEXT("/Game/GamePlay/Enemy/Boss/Sound/SC_MeteorHit.SC_MeteorHit"));
	if (SC_HITSOUND.Succeeded())
	{
		HitSound = SC_HITSOUND.Object;
	}
}

void ABossMeteorOverlapEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnBossMeteorOverlapEffect(this);
}

void ABossMeteorOverlapEffect::SetEffectEnable(bool Enable)
{
	Super::SetEffectEnable(Enable);

	if (Enable && HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
}
