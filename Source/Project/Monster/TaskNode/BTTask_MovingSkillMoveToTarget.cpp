// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/TaskNode/BTTask_MovingSkillMoveToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//
//EBTNodeResult::Type UBTTask_MovingSkillMoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	AAIController* AIController = OwnerComp.GetAIOwner();
//	if (!AIController)
//		return EBTNodeResult::Failed;
//
//	UBlackboardComponent * BlackboardComp = AIController->GetBlackboardComponent();
//	if (BlackboardComp)
//	{
//		BlackboardComp->SetValueAsBool(TEXT("IsMovingSkill"), false);
//		return EBTNodeResult::Succeeded;
//	}
//
//	return Super::ExecuteTask(OwnerComp, NodeMemory);;
//}
