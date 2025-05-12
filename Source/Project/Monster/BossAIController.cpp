// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossAIController.h"
#include "Monster/Boss.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ABossAIController::ABossAIController()
{
	//AI Setting
	//---------------------------------------------
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_BOSS(TEXT("/Game/GamePlay/Enemy/Boss/AI/BB_Boss.BB_Boss"));
	if (BB_BOSS.Succeeded())
	{
		BossBB = BB_BOSS.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_BOSS(TEXT("/Game/GamePlay/Enemy/Boss/AI/BT_Boss.BT_Boss"));
	if (BT_BOSS.Succeeded())
	{
		BossBT = BT_BOSS.Object;
	}
	//---------------------------------------------
}

void ABossAIController::MoveToTargetLocation(const FVector& TargetLocation)
{
	MoveToLocation(TargetLocation);
}

void ABossAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	ABoss * Boss = Cast<ABoss>(GetCharacter());
	if (Boss && Boss->GetPrevSkillIsDash())
	{
		Boss->DashEnd();
	}
}

void ABossAIController::StartBehaviorTree()
{
	if(BossBT)
		RunBehaviorTree(BossBT);
}

void ABossAIController::MontageEnd()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (BlackboardComp)
		BlackboardComp->SetValueAsBool(TEXT("IsPlayingMontage"), false);
}

void ABossAIController::SoulSiphonSkillEnd()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsBool(TEXT("IsPlayingMontage"), false);
		BlackboardComp->SetValueAsBool(TEXT("IsUsingSoulSiphon"), false);
		BlackboardComp->SetValueAsBool(TEXT("IllusionEnd"), false);
	}
}

void ABossAIController::SetUsingSoulSiphonState(bool Enable)
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (BlackboardComp)
		BlackboardComp->SetValueAsBool(TEXT("IsUsingSoulSiphon"), Enable);
}

void ABossAIController::SetUsingMontage()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (BlackboardComp)
		BlackboardComp->SetValueAsBool(TEXT("IsPlayingMontage"), true);
}

void ABossAIController::SetIllusionEnd(bool Enable)
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (BlackboardComp)
		BlackboardComp->SetValueAsBool(TEXT("IllusionEnd"), Enable);
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();
	
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BossBB, BlackboardComp))
	{
		AActor* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		BlackboardComp->SetValueAsObject(TEXT("Player"), Player);
	}
}
