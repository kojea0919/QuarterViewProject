#include "PlayerLocationActor/Phase3PlayerLocationActor.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

APhase3PlayerLocationActor::APhase3PlayerLocationActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APhase3PlayerLocationActor::BeginPlay()
{
	Super::BeginPlay();

	UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->SetPhase3PlayerTransform(GetActorTransform());
	}
}
