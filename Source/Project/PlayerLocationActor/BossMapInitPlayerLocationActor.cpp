#include "PlayerLocationActor/BossMapInitPlayerLocationActor.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

ABossMapInitPlayerLocationActor::ABossMapInitPlayerLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABossMapInitPlayerLocationActor::BeginPlay()
{
	Super::BeginPlay();

	UBossBattleSubSystem * SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->SetPlayerSpawnTransform(GetActorTransform());
	}
}
