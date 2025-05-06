// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Effect/BossSawToothSkillEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABossSawToothSkillEffect::ABossSawToothSkillEffect()
	:TelegraphComp(nullptr), NeedToUpdateScale(true), IsCanMove(false), CurMoveDistance(0.0f), MoveSpeed(2000.0f)
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_SAWTOOTH(TEXT("/Game/AdvancedMagicFX13/Particles/P_ky_cutter3.P_ky_cutter3"));
	if (PS_SAWTOOTH.Succeeded())
	{
		Effect->SetTemplate(PS_SAWTOOTH.Object);
	}

	TelegraphRectangleEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Enemy/Effect/Niagara/FX_Telegrap_Rectangle.FX_Telegrap_Rectangle"));
}

void ABossSawToothSkillEffect::OnTelegraphFinished(UNiagaraComponent* PSystem)
{
	IsCanMove = true;
}

void ABossSawToothSkillEffect::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnBossSawToothSkillEffect(this);
}

void ABossSawToothSkillEffect::StartTelegraphRectangle()
{
	NeedToUpdateScale = true;
	IsCanMove = false;
	CurMoveDistance = 0.0f;

	if (nullptr == TelegraphComp)
	{
		TelegraphComp = UNiagaraFunctionLibrary::SpawnSystemAttached(TelegraphRectangleEffect, RootComponent, NAME_None, FVector(), FRotator(0.0f, -90.0f, 0.0f), EAttachLocation::KeepRelativeOffset, false);

		TelegraphComp->SetVariableFloat(FName("User.Length"), SawToothMoveDistance);
		TelegraphComp->SetVariableFloat(FName("User.Width"), TelegraphRectangleWidth);
		TelegraphComp->SetVariableFloat(FName("User.LifeTime"), TelegraphRectangleLifeTime);

		TelegraphComp->OnSystemFinished.AddDynamic(this, &ABossSawToothSkillEffect::OnTelegraphFinished);
	}
	else
	{
		TelegraphComp->ResetSystem();
		TelegraphComp->Activate(true);
	}
	RootComponent->SetWorldScale3D(FVector(0.0f,1.0f,1.0f));
}

void ABossSawToothSkillEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (NeedToUpdateScale)
	{
		UpdateScale(DeltaTime);
	}

	if (IsCanMove)
	{
		UpdateLocation(DeltaTime);
	}
}

void ABossSawToothSkillEffect::UpdateScale(float DeltaTime)
{
	float CurScale = RootComponent->GetComponentScale().X;

	CurScale += DeltaTime * SawToothScaleSpeed;
	if (CurScale >= 1.0f)
	{
		CurScale = 1.0f;
		NeedToUpdateScale = false;
	}

	RootComponent->SetWorldScale3D(FVector(CurScale, 1.0f, 1.0f));
}

void ABossSawToothSkillEffect::UpdateLocation(float DeltaTime)
{
	float CurMoveLength = DeltaTime * MoveSpeed;

	if (CurMoveLength + CurMoveDistance >= SawToothMoveDistance)
	{
		IsCanMove = false;
		EffectObjPool->ReturnBossSawToothSkillEffect(this);
		return;
	}

	CurMoveDistance += CurMoveLength;

	AddActorWorldOffset(GetActorForwardVector() * CurMoveLength);
}
