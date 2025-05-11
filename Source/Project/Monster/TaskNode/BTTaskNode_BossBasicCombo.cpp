// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/TaskNode/BTTaskNode_BossBasicCombo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Monster/Boss.h"

EBTNodeResult::Type UBTTaskNode_BossBasicCombo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController * AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	ABoss* Boss = Cast<ABoss>(AIController->GetPawn());
	if (Boss)
	{
		Boss->BasicComboAttack();

		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool(TEXT("IsPlayingMontage"), true);
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
