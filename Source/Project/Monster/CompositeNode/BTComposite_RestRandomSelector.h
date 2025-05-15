// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BTComposite_RestRandomSelector.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTComposite_RestRandomSelector : public UBTCompositeNode
{
	GENERATED_BODY()


public:
	UBTComposite_RestRandomSelector(const FObjectInitializer& ObjectInitializer);

	virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
	virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;

	virtual int32 GetNextChildHandler(struct FBehaviorTreeSearchData& SearchData,
		int32 PrevChild, EBTNodeResult::Type LastResult) const override;


private:
	//mutable TArray<int32> ExecutedChildren;
	mutable int32 LastSuccessfulChildIdx;

};
