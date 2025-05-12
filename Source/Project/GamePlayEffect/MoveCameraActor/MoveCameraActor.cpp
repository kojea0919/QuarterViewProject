// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayEffect/MoveCameraActor/MoveCameraActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Archer/Archer.h"

AMoveCameraActor::AMoveCameraActor()
	: TargetCameraArmLength(600.f), CameraTransformSpeed(50.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	SetRootComponent(BoxCollider);

	BoxCollider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

}
void AMoveCameraActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AArcher * Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		Archer->SetTargetCameraRotation(TargetCameraRotator);
		Archer->SetTargetArmLength(TargetCameraArmLength);
		Archer->SetCameraTransformSpeed(CameraTransformSpeed);
		Archer->SetUpdateCameraTransform();
	}
}
void AMoveCameraActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMoveCameraActor::OnComponentBeginOverlap);
}

