// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/TaskNode/BTTaskNode_StoneSpike.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/Boss.h"

EBTNodeResult::Type UBTTaskNode_StoneSpike::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	ABoss* Boss = Cast<ABoss>(AIController->GetPawn());
	if (Boss)
	{
		Boss->StoneSpike();

		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsBool(TEXT("IsPlayingMontage"), true);
		}
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
