// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffectActor.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
}

void ABaseEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

