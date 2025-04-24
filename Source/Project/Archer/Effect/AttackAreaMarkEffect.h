// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/DecalEffectActor.h"
#include "AttackAreaMarkEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AAttackAreaMarkEffect : public ADecalEffectActor
{
	GENERATED_BODY()

public:
	AAttackAreaMarkEffect();

	virtual void Tick(float DeltaTime) override;

public:
	void SetController(class AArcherPlayerController* Controller) { ArcherController = Controller; }

	void SetCurSkillRange(float Range) { CurSkillRange = Range; }

private:
	virtual void LoadMaterial() override;

private:
	class AArcherPlayerController* ArcherController;

	float CurSkillRange;
};
