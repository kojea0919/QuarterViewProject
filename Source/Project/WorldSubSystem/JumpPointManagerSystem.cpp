// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldSubSystem/JumpPointManagerSystem.h"
#include "GamePlayEffect/JumpPointActor/JumpEndPoint.h"
#include "GamePlayEffect/JumpPointActor/JumpStartPoint.h"

void UJumpPointManagerSystem::AddJumpStartPoinArr(AJumpStartPoint* NewPoint)
{
	if (!NewPoint)
		return;
	JumpStartPointMap.Add(NewPoint->GetTagName(), NewPoint);
}

void UJumpPointManagerSystem::AddJumpEndPoinArr(AJumpEndPoint* NewPoint)
{
	if (!NewPoint)
		return;
	JumpEndPointMap.Add(NewPoint->GetTagName(), NewPoint);
}

const AJumpEndPoint* UJumpPointManagerSystem::GetJumpEndPoint(const FString& TagName)
{
	AJumpEndPoint** ReturnPoint = JumpEndPointMap.Find(TagName);
	if (ReturnPoint == nullptr)
		return nullptr;


	return *ReturnPoint;
}
