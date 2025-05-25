// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossMeteorEffect.h"
#include "Components/SphereComponent.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystemComponent.h"
#include "Monster/Effect/BossMeteorOverlapEffect.h"
#include "Archer/Archer.h"
#include "Kismet/GameplayStatics.h"
#include "DamageType/BossStiffDamageType.h"

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

	MeteorCollider->SetCollisionProfileName(TEXT("BossSkillCollision"));
	MeteorCollider->SetGenerateOverlapEvents(false);
}

void ABossMeteorEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurMoveLength = DeltaTime * FallSpeed;

	CurMoveDistance += CurMoveLength;

	AddActorWorldOffset(GetActorForwardVector() * CurMoveLength);

}

void ABossMeteorEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnBossMeteorEffect(this);
	CurMoveDistance = 0;
}

void ABossMeteorEffect::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MeteorCollider->SetGenerateOverlapEvents(false);
	ABossMeteorOverlapEffect * OverlapEffect = EffectObjPool->GetBossMeteorOverlapEffect();
	OverlapEffect->SetActorLocation(GetActorLocation());

	EffectObjPool->ReturnBossMeteorEffect(this);
	CurMoveDistance = 0;

	AArcher* Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		UGameplayStatics::ApplyDamage(
			Archer,
			MeteorDamage,
			GetInstigatorController(),
			this,
			UBossStiffDamageType::StaticClass());
	}

}

void ABossMeteorEffect::SetOverlapEventOn()
{
	MeteorCollider->SetGenerateOverlapEvents(true);
}

void ABossMeteorEffect::BeginPlay()
{
	Super::BeginPlay();
	MeteorCollider->SetGenerateOverlapEvents(false);
	MeteorCollider->OnComponentBeginOverlap.AddDynamic(this, &ABossMeteorEffect::OnComponentBeginOverlap);
}
