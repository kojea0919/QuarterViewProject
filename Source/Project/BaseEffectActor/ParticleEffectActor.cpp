// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticleEffectActor.h"

AParticleEffectActor::AParticleEffectActor()
	: Effect(nullptr)
{
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

void AParticleEffectActor::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	if (!Effect->IsActive())
		return;

	OnParticleSystemFinished_Impl();
}
