// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "JumpPointManagerSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UJumpPointManagerSystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void AddJumpStartPoinArr(class AJumpStartPoint* NewPoint);
	void AddJumpEndPoinArr(class AJumpEndPoint* NewPoint);

	const AJumpEndPoint* GetJumpEndPoint(const FString& TagName);

private:
	TMap<FString, class AJumpStartPoint*> JumpStartPointMap;
	TMap<FString, class AJumpEndPoint*> JumpEndPointMap;

};
