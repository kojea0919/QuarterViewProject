// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossAIController.h"
#include "Monster/Boss.h"

void ABossAIController::MoveToTargetLocation(const FVector& TargetLocation)
{
	MoveToLocation(TargetLocation);
}

void ABossAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	ABoss * Boss = Cast<ABoss>(GetCharacter());
	if (Boss)
		Boss->DashEnd();
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
}
