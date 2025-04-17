// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/DecalEffectActor.h"
#include "ArcherMoveSkillFootDecal.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherMoveSkillFootDecal : public ADecalEffectActor
{
	GENERATED_BODY()

public:
	AArcherMoveSkillFootDecal();

	virtual void Tick(float DeltaTime) override;

	void SetDecalRotation(FRotator Rotator);

	void StopUpdate() { StopUpdateRate = true; }

protected:
	virtual void BeginPlay() override;

private:
	virtual void LoadMaterial() override;

	void UpdateFootDecal(float DeltaTime);


private:
	float CurRate;

	float CurOpacity;

	//true면 CurRate 값을 바꾸는 것을 멈춘다.
	bool StopUpdateRate;
	
};
