// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/StoreNPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"

AStoreNPC::AStoreNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStoreNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStoreNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoreNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStoreNPC::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AArcher * Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		AArcherPlayerController * PlayerController = Archer->GetController<AArcherPlayerController>();
		if (PlayerController)
			PlayerController->SetVisibilityIntersectionKey(true);
	}
}

void AStoreNPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	AArcher* Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		AArcherPlayerController* PlayerController = Archer->GetController<AArcherPlayerController>();
		if (PlayerController)
			PlayerController->SetVisibilityIntersectionKey(false);
	}
}

