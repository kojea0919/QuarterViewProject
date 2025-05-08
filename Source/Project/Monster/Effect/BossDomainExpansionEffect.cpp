// Fill out your copyright notice in the Description page of Project Settings.


#include "BossDomainExpansionEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "WorldSubSystem/EffectObjectPool.h"


ABossDomainExpansionEffect::ABossDomainExpansionEffect()
	: CurTime(0)
{
	PrimaryActorTick.bCanEverTick = true;

	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/NS_DomainExpansion.NS_DomainExpansion"));

	//Curve Setting
	//---------------------------------------------
	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_RADIUSCURVE(TEXT("/Game/GamePlay/GamePlayEffect/BlackAndWhite/C_BlackAndWhiteRadius.C_BlackAndWhiteRadius"));
	if (C_RADIUSCURVE.Succeeded())
	{
		ScaleCurve = C_RADIUSCURVE.Object;
	}
	//---------------------------------------------
}

void ABossDomainExpansionEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnBossDomainExpansionEffect(this);

	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ABossDomainExpansionEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	PrimaryActorTick.bStartWithTickEnabled = true;
	NiagaraComp->SetWorldScale3D(FVector(0.0f));
}

void ABossDomainExpansionEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurTime += DeltaTime;
	if (CurTime >= MaxTime)
	{
		CurTime = 0;

		EffectObjPool->ReturnBossDomainExpansionEffect(this);
		return; 
	}

	float CurScale = ScaleCurve->GetFloatValue(CurTime);

	if(NiagaraComp)
		NiagaraComp->SetWorldScale3D(FVector(CurScale / 50.0f));
}
