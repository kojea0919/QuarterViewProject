// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalEffectActor.h"
#include "Components/DecalComponent.h"

ADecalEffectActor::ADecalEffectActor()
{
	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("SCENE"));
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("DECAL"));

	RootComponent = DefaultScene;
	Decal->SetupAttachment(DefaultScene);
}

void ADecalEffectActor::SetEffectEnable(bool Enable)
{
	SetActorHiddenInGame(!Enable);
}

void ADecalEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadMaterial();
}
;