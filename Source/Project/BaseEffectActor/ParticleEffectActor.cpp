// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleEffectActor.h"
#include "Particles/ParticleSystemComponent.h"

AParticleEffectActor::AParticleEffectActor()
	: Effect(nullptr), EffectEnable(true)
{
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	RootComponent = Effect;
}

void AParticleEffectActor::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != Effect)
		Effect->OnSystemFinished.AddDynamic(this, &AParticleEffectActor::OnParticleSystemFinished);
}

void AParticleEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParticleEffectActor::SetEffectEnable(bool Enable)
{
	SetActorHiddenInGame(!Enable);

	if (!Effect)
		return;

	EffectEnable = Enable;
	if (Enable)
	{
		Effect->Activate(true);
	}
	else
	{
		Effect->Deactivate();
	}
}

void AParticleEffectActor::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{	
	if (!EffectEnable)
		return;

	OnParticleSystemFinished_Impl();
}
