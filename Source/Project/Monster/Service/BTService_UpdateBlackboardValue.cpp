// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Service/BTService_UpdateBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateBlackboardValue::UBTService_UpdateBlackboardValue()
{
	bNotifyOnSearch = true;
}

void UBTService_UpdateBlackboardValue::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	UBlackboardComponent * Blackboard = SearchData.OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
		return;

	AActor * Boss = Cast<AActor>(Blackboard->GetValueAsObject(TEXT("SelfActor")));
	AActor * Player = Cast<AActor>(Blackboard->GetValueAsObject(TEXT("Player")));

	if (!Boss || !Player)
		return;


	float Distance = (Boss->GetActorLocation() - Player->GetActorLocation()).Length();

	Blackboard->SetValueAsFloat(TEXT("PlayerToBossDistance"), Distance);


}
