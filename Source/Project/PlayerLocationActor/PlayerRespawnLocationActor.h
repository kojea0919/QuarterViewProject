#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerRespawnLocationActor.generated.h"

UCLASS()
class PROJECT_API APlayerRespawnLocationActor : public AActor
{
	GENERATED_BODY()
	

public:
	APlayerRespawnLocationActor();

protected:
	virtual void BeginPlay() override;

};
