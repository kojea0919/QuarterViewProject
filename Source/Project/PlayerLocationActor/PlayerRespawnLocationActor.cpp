#include "PlayerLocationActor/PlayerRespawnLocationActor.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

APlayerRespawnLocationActor::APlayerRespawnLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APlayerRespawnLocationActor::BeginPlay()
{
	Super::BeginPlay();
	
	UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->SetPlayerRespawnTransform(GetActorTransform());
	}
}

