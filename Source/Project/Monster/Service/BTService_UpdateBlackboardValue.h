// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateBlackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTService_UpdateBlackboardValue : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateBlackboardValue();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;

};
