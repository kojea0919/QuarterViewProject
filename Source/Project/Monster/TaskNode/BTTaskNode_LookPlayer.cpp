// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/TaskNode/BTTaskNode_LookPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/Boss.h"

UBTTaskNode_LookPlayer::UBTTaskNode_LookPlayer()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_LookPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_LookPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ABoss* Boss = Cast<ABoss>(AIController->GetPawn());
	if (!Boss)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
	if (!Blackboard)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if(Boss->LookPlayer(DeltaSeconds))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Blackboard->SetValueAsBool(TEXT("IsRotateToPlayer"), false);

		return;
	}
	else
	{
		Blackboard->SetValueAsBool(TEXT("IsRotateToPlayer"), true);
	}
}
