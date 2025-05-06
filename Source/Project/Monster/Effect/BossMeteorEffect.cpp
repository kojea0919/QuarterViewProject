// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossMeteorEffect.h"
#include "Components/SphereComponent.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystemComponent.h"


ABossMeteorEffect::ABossMeteorEffect()
	: CurMoveDistance(0)
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_METEOR(TEXT("/Game/ParagonGideon/FX/Particles/Gideon/Abilities/ProjectileMeteor/FX/P_Gideon_RMB_Proj.P_Gideon_RMB_Proj"));
	if (PS_METEOR.Succeeded())
	{
		Effect->SetTemplate(PS_METEOR.Object);
	}

	MeteorCollider = CreateDefaultSubobject<USphereComponent>(TEXT("COLLIDER"));

	SetRootComponent(MeteorCollider);
	Effect->SetupAttachment(MeteorCollider);

	//MeteorCollider->SetWorldScale3D(FVector(0.5f));


	//Effect->bUseFixedRelativeBoundingBox = true;
	//Effect->FixedRelativeBoundingBox = FBox(FVector(-2000, -2000, -2000), FVector(2000, 2000, 2000));
}

void ABossMeteorEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurMoveLength = DeltaTime * FallSpeed;

	if (CurMoveLength + CurMoveDistance >= 3000.0f)
	{
		EffectObjPool->ReturnBossMeteorEffect(this);
		CurMoveDistance = 0;
		return;
	}

	CurMoveDistance += CurMoveLength;

	AddActorWorldOffset(GetActorForwardVector() * CurMoveLength);

}

void ABossMeteorEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnBossMeteorEffect(this);
}
