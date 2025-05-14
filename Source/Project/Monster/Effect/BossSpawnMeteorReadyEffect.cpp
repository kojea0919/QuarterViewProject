// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossSpawnMeteorReadyEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DamageType/BossKnockBackDamageType.h"

ABossSpawnMeteorReadyEffect::ABossSpawnMeteorReadyEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Circle.FX_Telegrap_Circle"));
}

void ABossSpawnMeteorReadyEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturntBossSpawnMeteorReadyEffect(this);

	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel4);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector SphereLocation = GetActorLocation();

	bool IsHit = GetWorld()->SweepMultiByObjectType(HitResults,
		SphereLocation, SphereLocation,
		GetActorQuat(), ObjectQueryParams,
		FCollisionShape::MakeSphere(TelegraphRadius/2),
		Params);

	DrawDebugSphere(GetWorld(),
		SphereLocation,
		TelegraphRadius/2, 12,
		FColor::Green, false, 2);

	//충돌이 된 경우
	if (IsHit)
	{
		for (auto& Hit : HitResults)
		{

			UGameplayStatics::ApplyDamage(
				Hit.GetActor(),
				Damage,
				GetInstigatorController(),
				this,
				UBossKnockBackDamageType::StaticClass());
		}
	}
}

void ABossSpawnMeteorReadyEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	if (NiagaraComp)
	{
		NiagaraComp->SetVariableFloat(FName("User.Scale"), TelegraphRadius);
		NiagaraComp->SetVariableFloat(FName("User.LifeTime"), TelegraphRectangleLifeTime);
		NiagaraComp->SetVariableFloat(FName("User.CircleAngle"), 360);
	}
}
