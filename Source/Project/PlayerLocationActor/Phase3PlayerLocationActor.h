#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Phase3PlayerLocationActor.generated.h"

UCLASS()
class PROJECT_API APhase3PlayerLocationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APhase3PlayerLocationActor();

protected:
	virtual void BeginPlay() override;
};
