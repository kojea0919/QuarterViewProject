#include "PlayerLocationActor/Phase3BossLocationActor.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

APhase3BossLocationActor::APhase3BossLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APhase3BossLocationActor::BeginPlay()
{
	Super::BeginPlay();

	UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->SetPhase3BossTransform(GetActorTransform());
	}
}

