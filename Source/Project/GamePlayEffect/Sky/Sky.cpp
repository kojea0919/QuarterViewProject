#include "GamePlayEffect/Sky/Sky.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

ASky::ASky()
{
 		PrimaryActorTick.bCanEverTick = false;

}

void ASky::BeginPlay()
{
	Super::BeginPlay();
	
	UBossBattleSubSystem * SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		if(IsBurn)
			SubSystem->SetBurnSky(this);
		else
			SubSystem->SetDeathSky(this);
	}

}

