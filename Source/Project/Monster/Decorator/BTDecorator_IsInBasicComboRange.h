// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInBasicComboRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTDecorator_IsInBasicComboRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsInBasicComboRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
