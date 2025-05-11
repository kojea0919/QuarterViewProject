// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CompositeNode/BTComposite_RandomSelector.h"

UBTComposite_RandomSelector::UBTComposite_RandomSelector(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), LastSuccessfulChildIdx(INDEX_NONE)
{
	NodeName = TEXT("Random Selector");
}

void UBTComposite_RandomSelector::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FBTCompositeMemory>(NodeMemory, InitType);
	//ExecutedChildren.Empty();
	LastSuccessfulChildIdx = INDEX_NONE;
}

void UBTComposite_RandomSelector::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FBTCompositeMemory>(NodeMemory, CleanupType);
	//ExecutedChildren.Empty();
	LastSuccessfulChildIdx = INDEX_NONE;
}

int32 UBTComposite_RandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
	//BTSpecialChild::ReturnToParent
	//부모 노드로 돌아가기에 대한 인덱스 특수값
	int32 NextChildIdx = BTSpecialChild::ReturnToParent;

	//BTSpecialChild::NotInitialized
	//아직 초기화가 안됨을 나타내는 인덱스 특수값 == INDEX_NONE
	if (PrevChild == BTSpecialChild::NotInitialized)
	{
		//현재 가지고 있는 자식 내에서 랜덤 idx 설정
		NextChildIdx = FMath::RandRange(0, GetChildrenNum() - 1);

		//이전에 성공한 인덱스와 동일하면 다음 Child로 선택
		if (NextChildIdx == LastSuccessfulChildIdx && GetChildrenNum() > 1)
		{
			NextChildIdx = (NextChildIdx + 1) % GetChildrenNum();
		}
	}
	else
	{
		if (LastResult == EBTNodeResult::Succeeded)
		{
			LastSuccessfulChildIdx = PrevChild;
			//ExecutedChildren.Empty();
			return BTSpecialChild::ReturnToParent;
		}
		if (LastResult == EBTNodeResult::Failed)
		{
			//실패시 새로운 인덱스를 만들어서 해당 스킬 진행
			int NewNextChildIdx = FMath::RandRange(0, GetChildrenNum() - 1);

			if (NextChildIdx == NewNextChildIdx)
			{
				NextChildIdx = (NextChildIdx + 1) % GetChildrenNum();
			}
		}

		/*else if (LastResult == EBTNodeResult::Failed)
		{
			ExecutedChildren.Add(PrevChild);

			if (ExecutedChildren.Num() >= GetChildrenNum())
			{
				ExecutedChildren.Empty();
				LastSuccessfulChildIdx = INDEX_NONE;
				return BTSpecialChild::ReturnToParent;
			}

			TArray<int32> AvailableChildren;
			for (int32 ChildIdx = 0; ChildIdx < GetChildrenNum(); ++ChildIdx)
			{
				if (!ExecutedChildren.Contains(ChildIdx))
				{
					AvailableChildren.Add(ChildIdx);
				}
			}

			NextChildIdx = AvailableChildren[FMath::RandRange(0, AvailableChildren.Num() - 1)];
		}*/
	}

	return NextChildIdx;;
}
