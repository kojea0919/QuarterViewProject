// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/TaskNode/BTTaskNode_SoulSiphon.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/Boss.h"

EBTNodeResult::Type UBTTaskNode_SoulSiphon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	ABoss* Boss = Cast<ABoss>(AIController->GetPawn());
	if (Boss)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard->GetValueAsBool(TEXT("IsUsingSoulSiphon")))
			return  EBTNodeResult::Failed;

		Boss->SoulSiphon();

		if (Blackboard)
		{
			Blackboard->SetValueAsBool(TEXT("IsPlayingMontage"), true);
		}
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
