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
	//캐릭터 몸을 빛나게 하는 강도 0에 가까울 수록 강도 증가
	float CurEmissiveIntensity;

	float EmissiveSpeed;
	
};
