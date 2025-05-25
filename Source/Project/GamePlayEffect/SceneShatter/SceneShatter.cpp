// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayEffect/SceneShatter/SceneShatter.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Field/FieldSystemComponent.h"

ASceneShatter::ASceneShatter()
{
	GeometryCollectionComponent = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("BREAK"));
	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PLANE"));

	GeometryCollectionComponent->SetupAttachment(RootComponent);
	Plane->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PLANE(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (SM_PLANE.Succeeded())
	{
		Plane->SetStaticMesh(SM_PLANE.Object);
	}
}

void ASceneShatter::BeginPlay()
{
	Super::BeginPlay();

	/*static ConstructorHelpers::FObjectFinder<UGeometryCollection> GC(TEXT("/Game/GamePlay/GamePlayEffect/SceneShatter/Text_Text/GC_SceneShatterMesh.GC_SceneShatterMesh"));
	if (GC.Succeeded())
	{
		GeometryCollectionComponent->SetRestCollection(GC.Object);
	}*/

	UGeometryCollection* LoadedGC = Cast<UGeometryCollection>(StaticLoadObject(UGeometryCollection::StaticClass(), nullptr, TEXT("/Game/GamePlay/GamePlayEffect/SceneShatter/Text_Text/GC_SceneShatterMesh.GC_SceneShatterMesh")));
	if (LoadedGC)
	{
		GeometryCollectionComponent->SetRestCollection(LoadedGC);
	}
	else
	{
		return;
	}

	GeometryCollectionComponent->SetSimulatePhysics(true);
	GeometryCollectionComponent->SetEnableGravity(false);

	FJsonSerializableArrayFloat DamageThresholdArr;
	DamageThresholdArr.Push(100);
	DamageThresholdArr.Push(100);
	DamageThresholdArr.Push(100);
	GeometryCollectionComponent->SetDamageThreshold(DamageThresholdArr);

	GetCaptureComponent2D()->bCaptureOnMovement = false;
	GeometryCollectionComponent->SetEnableGravity(false);
	GeometryCollectionComponent->BodyInstance.LinearDamping = 5.0f; // 느리게 떨어지도록
	GeometryCollectionComponent->BodyInstance.AngularDamping = 5.0f;
}
