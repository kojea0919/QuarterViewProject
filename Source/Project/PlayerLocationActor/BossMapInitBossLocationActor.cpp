#include "PlayerLocationActor/BossMapInitBossLocationActor.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

ABossMapInitBossLocationActor::ABossMapInitBossLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ABossMapInitBossLocationActor::BeginPlay()
{
	Super::BeginPlay();

	UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->SetBossSpawnTransform(GetActorTransform());
	}
}

