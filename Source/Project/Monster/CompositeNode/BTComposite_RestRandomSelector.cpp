// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CompositeNode/BTComposite_RestRandomSelector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTComposite_RestRandomSelector::UBTComposite_RestRandomSelector(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("RestRandom Selector");
}

void UBTComposite_RestRandomSelector::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FBTCompositeMemory>(NodeMemory, InitType);
}

void UBTComposite_RestRandomSelector::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FBTCompositeMemory>(NodeMemory, CleanupType);
}

int32 UBTComposite_RestRandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	if (LastResult == EBTNodeResult::Succeeded)
	{
		LastSuccessfulChildIdx = PrevChild;
		//ExecutedChildren.Empty();
		return BTSpecialChild::ReturnToParent;
	}

	bool IsRotation = false;

	//현재 가지고 있는 자식 내에서 랜덤 idx 설정
	NextChildIdx = FMath::RandRange(0, GetChildrenNum());

	if (NextChildIdx == 0 || NextChildIdx == 3)
	{
		NextChildIdx = 0;
		
		IsRotation = true;
	}
	AAIController* AIController = SearchData.OwnerComp.GetAIOwner();
	if (!AIController)
		return BTSpecialChild::ReturnToParent;

	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(TEXT("PrevRestIsRotation"), IsRotation);
	}

	return NextChildIdx;;
}
