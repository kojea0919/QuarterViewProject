#include "GamePlayEffect/SolarEclipse/SolarEclipse.h"
#include "Components/StaticMeshComponent.h"

ASolarEclipse::ASolarEclipse()
	: EclipseStart(false), CurTime(0)
{
	PrimaryActorTick.bCanEverTick = true;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLANE"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PLANE(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (SM_PLANE.Succeeded())
	{
		Plane->SetStaticMesh(SM_PLANE.Object);
	}

	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_PROGRESSCURVE(TEXT("/Game/GamePlay/GamePlayEffect/SolarEclipse/CF_SolarEclipseProgress.CF_SolarEclipseProgress"));

	if (C_PROGRESSCURVE.Succeeded())
	{
		SolarEclipseProgressCurve = C_PROGRESSCURVE.Object;
	}
}

void ASolarEclipse::SolarEclipseStart()
{
	EclipseStart = true;
}

void ASolarEclipse::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASolarEclipse::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/GamePlayEffect/SolarEclipse/MI_SolarEclipse.MI_SolarEclipse"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, Plane->GetStaticMesh());
	Plane->SetMaterial(0, DynMaterial);

	DynMaterial->SetScalarParameterValue(FName("ChargingEffectEnable"), 0.0f);
}

void ASolarEclipse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EclipseStart)
	{
		CurTime += DeltaTime;
		float ProgressRate = SolarEclipseProgressCurve->GetFloatValue(CurTime);

		DynMaterial->SetScalarParameterValue(TEXT("Progress"), ProgressRate);

		if (CurTime >= 4)
		{
			EclipseStart = false;
			CurTime = 0;
		}
	}
}

