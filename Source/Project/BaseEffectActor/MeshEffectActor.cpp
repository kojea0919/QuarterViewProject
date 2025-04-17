// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshEffectActor.h"

AMeshEffectActor::AMeshEffectActor()
{
}

void AMeshEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMeshEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadMaterial();
}

void AMeshEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeshEffectActor::SetEffectEnable(bool Enable)
{
	SetActorHiddenInGame(!Enable);
}

