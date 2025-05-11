// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_LookPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTaskNode_LookPlayer : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_LookPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
