// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossStoneSpikeAreaMarkEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Archer/Archer.h"
#include "Kismet/GameplayStatics.h"
#include "DamageType/BossKnockBackDamageType.h"
#include "Monster/Boss.h"
#include "Monster/BossAIController.h"

ABossStoneSpikeAreaMarkEffect::ABossStoneSpikeAreaMarkEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Circle.FX_Telegrap_Circle"));
}

void ABossStoneSpikeAreaMarkEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnBossStoneSpikeAreaMarkEffect(this);

	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel4);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector SphereLocation = GetActorLocation();

	bool IsHit = GetWorld()->SweepMultiByObjectType(HitResults,
		SphereLocation, SphereLocation,
		GetActorQuat(), ObjectQueryParams,
		FCollisionShape::MakeSphere(TelegraphRadius / 2),
		Params);

	/*DrawDebugSphere(GetWorld(),
		SphereLocation,
		TelegraphRadius / 2, 12,
		FColor::Green, false, 2);*/

	//충돌이 된 경우
	if (IsHit)
	{
		for (auto& Hit : HitResults)
		{
			//Actor가 장판 각도 안에 있는 경우에만 데미지 전달
			//----------------------------------------------
			FVector EffectToActorVector = Hit.GetActor()->GetActorLocation() - GetActorLocation();
			EffectToActorVector.Normalize();
			float YawDiff = FMath::Abs(GetActorRotation().Yaw - EffectToActorVector.Rotation().Yaw);
			//----------------------------------------------


			if (YawDiff <= TelegraphAngle / 2)
			{
				UGameplayStatics::ApplyDamage(
					Hit.GetActor(),
					StoneSpikeDamage,
					GetInstigatorController(),
					this,
					UBossKnockBackDamageType::StaticClass());
			}
		}
	}
}

void ABossStoneSpikeAreaMarkEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	if (NiagaraComp)
	{
		NiagaraComp->SetVariableFloat(FName("User.Scale"), TelegraphRadius);
		NiagaraComp->SetVariableFloat(FName("User.LifeTime"), TelegraphLifeTime);
		NiagaraComp->SetVariableFloat(FName("User.CircleAngle"), TelegraphAngle);
	}
}
