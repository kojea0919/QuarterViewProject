#include "GamePlayEffect/HideMap/HideMapComponent.h"

AHideMapComponent::AHideMapComponent()
{
	PrimaryActorTick.bCanEverTick = false;

	MapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MAPCOMPONENT"));


	SetRootComponent(MapComponent);
	MapComponent->SetCollisionProfileName(TEXT("VisibleOnOffMapComponent"));
}

void AHideMapComponent::SetOpacityMask(float Mask)
{
	int32 Num = DynMaterialArr.Num();
	for (int32 i = 0; i < Num; ++i)
	{
		DynMaterialArr[i]->SetScalarParameterValue(TEXT("OpacityMask"), Mask);
	}
}

void AHideMapComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<UMaterialInterface*> Materials = MapComponent->GetMaterials();
	int32 Num = Materials.Num();
	for (int32 i = 0; i < Num; ++i)
	{
		UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(Materials[i], MapComponent->GetStaticMesh());
		MapComponent->SetMaterial(i, DynMaterial);
		DynMaterialArr.Add(DynMaterial);
	}
}

