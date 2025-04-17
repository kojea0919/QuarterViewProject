// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSkillAnimNotifyState.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/ArcherPlayerController.h"

UMoveSkillAnimNotifyState::UMoveSkillAnimNotifyState()
	: CurEmissiveIntensity(0.0f), EmissiveSpeed(1.0f)
{
}

void UMoveSkillAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AArcher* Archer = Cast<AArcher>(MeshComp->GetOwner());
	if (nullptr == Archer)
		return;

	CurEmissiveIntensity = 0.0f;
	Archer->SetMoveSkillEmissiveIntensity(CurEmissiveIntensity);
}

void UMoveSkillAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	//MoveSkill Effect를 위한 이미시브 강도 Update
	//---------------------------------------------------------------
	CurEmissiveIntensity += EmissiveSpeed * FrameDeltaTime;
	CurEmissiveIntensity = FMath::Clamp(CurEmissiveIntensity, 0.0f, 1.0f);
	//---------------------------------------------------------------

	AArcher* Archer = Cast<AArcher>(MeshComp->GetOwner());
	if (nullptr == Archer)
		return;

	Archer->SetMoveSkillEmissiveIntensity(CurEmissiveIntensity);
}

void UMoveSkillAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	CurEmissiveIntensity = 1.0f;

	AArcher* Archer = Cast<AArcher>(MeshComp->GetOwner());
	if (nullptr == Archer)
		return;

	Archer->SetMoveSkillEmissiveIntensity(CurEmissiveIntensity);
	Archer->SetMoveSkillOn(false);
}
