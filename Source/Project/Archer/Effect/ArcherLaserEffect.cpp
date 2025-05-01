// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Effect/ArcherLaserEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystemComponent.h"

AArcherLaserEffect::AArcherLaserEffect()
	: DynMaterial(nullptr) ,InitLength(30.0f), InitScale(2.0f), CurScale(2.0f),
	ScaleDecreaseSpeed(2.5f)
{
	PrimaryActorTick.bCanEverTick = true;

	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CYLINDER"));
	LaserBeam = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LASERBEAM"));

	RootComponent = Cylinder;

	//Cylinder Setting
	//--------------------------------------------------------------------------
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CYLINDER(TEXT("/Game/Player/Archer/Effect/Mesh/SM_Cylinder.SM_Cylinder"));
	if (SM_CYLINDER.Succeeded())
	{
		Cylinder->SetStaticMesh(SM_CYLINDER.Object);
	}

	Cylinder->SetCollisionProfileName(TEXT("NoCollision"));
	Cylinder->SetWorldScale3D(FVector(0.5f, 0.5f, InitLength));
	//--------------------------------------------------------------------------


	//LaserBeam Setting
	//--------------------------------------------------------------------------
	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_BEAM(TEXT("/Game/Player/Archer/Effect/Particle/P_Beam.P_Beam"));
	if (P_BEAM.Succeeded())
	{
		LaserBeam->SetTemplate(P_BEAM.Object);
	}
	//--------------------------------------------------------------------------

	//SetTickEnable(true);
}

void AArcherLaserEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateScale(DeltaTime);

	LaserBeam->SetBeamSourcePoint(0, GetActorLocation(), 0);
	LaserBeam->SetBeamTargetPoint(0, GetActorLocation() + GetActorUpVector() * InitLength * 19.5f, 0);
}

void AArcherLaserEffect::UpdateScale(float DeltaTime)
{
	CurScale -= DeltaTime * ScaleDecreaseSpeed;

	if (CurScale <= 0.0f)
	{
		EffectObjPool->ReturnArcherLaserEffect(this);
		CurScale = InitScale;
	}
	else
	{		
		Cylinder->SetWorldScale3D(FVector(CurScale, CurScale, InitLength));
		LaserBeam->SetWorldScale3D(FVector(CurScale * 3, CurScale * 3, 1.0f));
	}
}

void AArcherLaserEffect::LoadMaterial()
{
	UMaterialInstance* Material = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Player/Archer/Effect/Mesh/Material/M_ArcherLaser_Inst.M_ArcherLaser_Inst"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, Cylinder->GetStaticMesh());
	Cylinder->SetMaterial(0, DynMaterial);
}
