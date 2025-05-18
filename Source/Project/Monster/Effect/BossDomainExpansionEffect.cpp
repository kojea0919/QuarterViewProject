// Fill out your copyright notice in the Description page of Project Settings.


#include "BossDomainExpansionEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Archer/ArcherPlayerController.h"
#include "Monster/Boss.h"

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
	IsReverse = false;

	ABoss* Boss = Cast<ABoss>(GetOwner());
	if (Boss)
	{
		Boss->ClearDomainExpansionEffect();
	}
}

void ABossDomainExpansionEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	PrimaryActorTick.bStartWithTickEnabled = true;
	NiagaraComp->SetWorldScale3D(FVector(0.0f));
	CurTime = 0.f;
}

void ABossDomainExpansionEffect::SetEffectEnable(bool Enable)
{
	Super::SetEffectEnable(Enable);
}

void ABossDomainExpansionEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurTime += DeltaTime;
	if (CurTime >= MaxTime)
	{
		if (IsReverse)
		{
			AArcherPlayerController * Controller=  Cast<AArcherPlayerController>(GetWorld()->GetFirstPlayerController());
			if (Controller)
			{
				Controller->StopPlayerSlow();
			}
		}


		CurTime = 0;
		EffectObjPool->ReturnBossDomainExpansionEffect(this);

		ABoss* Boss = Cast<ABoss>(GetOwner());
		if (Boss)
		{
			Boss->ClearDomainExpansionEffect();
		}

		return; 
	}

	float CurScale;
	if (IsReverse)
	{
		CurScale = ScaleCurve->GetFloatValue((MaxTime-CurTime) * 0.67);
	}
	else
	{
		CurScale = ScaleCurve->GetFloatValue(CurTime* 0.67);
	}

	if(NiagaraComp)
		NiagaraComp->SetWorldScale3D(FVector(CurScale / 33.3f));
}
