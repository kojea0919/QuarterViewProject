// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Decorator/BTDecorator_IsInBasicComboRange.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Monster/Boss.h"

UBTDecorator_IsInBasicComboRange::UBTDecorator_IsInBasicComboRange()
{
	NodeName = TEXT("IsInBasicComboAttackRange");
}

bool UBTDecorator_IsInBasicComboRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController * AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return false;

	ABoss* Boss = Cast<ABoss>(AIController->GetPawn());
	if (!Boss)
		return false;

	if (Boss->GetDistanceToPlayer() < Boss->GetBasicComboAttackRange())
		return true;

	return false;
}
