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

	static ConstructorHelpers::FObjectFinder<UGeometryCollection> GC(TEXT("/Game/GamePlay/GamePlayEffect/SceneShatter/Text_Text/GC_SceneShatter.GC_SceneShatter"));
	if (GC.Succeeded())
	{
		GeometryCollectionComponent->SetRestCollection(GC.Object);

		FJsonSerializableArrayFloat DamageThresholdArr;
		DamageThresholdArr.Push(0);
		DamageThresholdArr.Push(0);
		DamageThresholdArr.Push(0);
		GeometryCollectionComponent->SetDamageThreshold(DamageThresholdArr);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PLANE(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (SM_PLANE.Succeeded())
	{
		Plane->SetStaticMesh(SM_PLANE.Object);
	}

	FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("test"));
	FieldSystem->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	GetCaptureComponent2D()->bCaptureOnMovement = false;
	GeometryCollectionComponent->SetEnableGravity(false);
}

void ASceneShatter::Shatter()
{

	FieldSystem->ApplyRadialForce(true, GetActorLocation(), 25000.0f);
	GeometryCollectionComponent->AddImpulseAtLocation(FVector(100.0f, 0.0f, 0.0f), FVector(GetActorLocation()));
}

	/*UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorLocation().ToString());

	FieldSystem->ApplyRadialForce(true, GetActorLocation(), 500.0f);*/
	//GeometryCollectionComponent->AddImpulseAtLocation(FVector(100.0f, 0.0f, 0.0f), FVector(GetActorLocation()));


void ASceneShatter::BeginPlay()
{
	Super::BeginPlay();

	GeometryCollectionComponent->SetSimulatePhysics(true);


	//GeometryCollectionComponent->AddImpulseAtLocation(FVector(6000.0f, 0.0f, 0.0f), FVector(GetActorLocation()));
	//GeometryCollectionComponent->SetEnableGravity(true);
	//GeometryCollectionComponent->ApplyPhysicsField(true, EGeometryCollectionPhysicsTypeEnum::)
	//UGameplayStatics::ApplyRadialDamage(GeometryCollection,100,100,100)
}
