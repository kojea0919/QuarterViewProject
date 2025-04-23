// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAreaMarkEffect.h"
#include "Components/DecalComponent.h"
#include "Project/Archer/ArcherPlayerController.h"

AAttackAreaMarkEffect::AAttackAreaMarkEffect()
	: ArcherController(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void AAttackAreaMarkEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(ArcherController->GetMouseWorldLocation());
}

void AAttackAreaMarkEffect::LoadMaterial()
{
	UMaterialInstance* BaseDecalMaterial = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Player/Archer/AttackAreaMark/M_AttackAreaMark_Inst.M_AttackAreaMark_Inst"));

	DynMaterial = UMaterialInstanceDynamic::Create(BaseDecalMaterial, this);
	Decal->SetDecalMaterial(DynMaterial);
}
