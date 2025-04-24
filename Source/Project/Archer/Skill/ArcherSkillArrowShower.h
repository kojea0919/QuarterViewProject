// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase/ChargingSkill/ChargingSkill.h"
#include "ArcherSkillArrowShower.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherSkillArrowShower : public UChargingSkill
{
	GENERATED_BODY()

public:
	UArcherSkillArrowShower();

	virtual bool Use();

	virtual void ReleaseEffect();
	
public:
	void CreateSkillEffect();

protected:
	virtual void CompleteChargingProc() override;	//차징 성공 처리 함수

private:
	float Range;

	FTimerHandle EffectCreateTimer;					//스킬 사용후 잠시후 이펙트 생성을 위한 Timer
	float EffectTermTime;
};
