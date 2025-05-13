#include "GamePlayEffect/JumpPointActor/JumpEndPoint.h"
#include "WorldSubSystem/JumpPointManagerSystem.h"

AJumpEndPoint::AJumpEndPoint()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AJumpEndPoint::BeginPlay()
{
	Super::BeginPlay();
	

	UJumpPointManagerSystem* Manager = GetWorld()->GetSubsystem<UJumpPointManagerSystem>();
	if (!Manager)
		return;
	Manager->AddJumpEndPoinArr(this);
}

void AJumpEndPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

