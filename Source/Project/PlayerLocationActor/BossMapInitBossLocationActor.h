#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossMapInitBossLocationActor.generated.h"

UCLASS()
class PROJECT_API ABossMapInitBossLocationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossMapInitBossLocationActor();

protected:
	virtual void BeginPlay() override;

};
