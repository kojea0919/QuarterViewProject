#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Phase3BossLocationActor.generated.h"

UCLASS()
class PROJECT_API APhase3BossLocationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APhase3BossLocationActor();

protected:
	virtual void BeginPlay() override;

};
