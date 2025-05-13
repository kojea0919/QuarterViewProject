// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossMapInitPlayerLocationActor.generated.h"

UCLASS()
class PROJECT_API ABossMapInitPlayerLocationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossMapInitPlayerLocationActor();

protected:
	virtual void BeginPlay() override;


};
