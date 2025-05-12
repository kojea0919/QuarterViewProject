// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABossAIController();

public:
	void MoveToTargetLocation(const FVector& TargetLocation);
	
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	void StartBehaviorTree();

	void MontageEnd();
	void SoulSiphonSkillEnd();

	void SetUsingSoulSiphonState(bool Enable);
	void SetUsingMontage();

	void SetIllusionEnd(bool Enable);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class UBehaviorTree* BossBT;

	UPROPERTY()
	class UBlackboardData* BossBB;
};
