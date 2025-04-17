// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MoveSkillAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMoveSkillAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UMoveSkillAnimNotifyState();

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	//ĳ���� ���� ������ �ϴ� ���� 0�� ����� ���� ���� ����
	float CurEmissiveIntensity;

	float EmissiveSpeed;
	
};
