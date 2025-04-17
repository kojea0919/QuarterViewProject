// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseSkill.h"
#include "ChargingSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UChargingSkill : public UBaseSkill
{
	GENERATED_BODY()
	
public:
	UChargingSkill();

	virtual bool Use() override;
	virtual void ReleaseSkill() override;
	virtual void End() override;

public:
	void SetCharginSpeed(float Speed) { ChargingSpeed = Speed; }
	void SetTotalChargingTime(float TotalTime) { TotalChargingTime = TotalTime; }
	void SetSkillGaugeBar(class USkillGaugeBar* Widget) { if (nullptr == SkillGaugeBar) SkillGaugeBar = Widget; }
	void SetIsLookMouse(bool Enable) { IsLookMouse = Enable; }

	float GetChargingSpeed() const { return ChargingSpeed; }
	float GetTotalChargingTime() const { return TotalChargingTime; }

private:
	void ResetSkillState();

private:
	float ChargingSpeed;		//차징 속도
	float TotalChargingTime;	//스킬을 사용하는데 필요한 차징 시간
	
	bool IsLookMouse;			//마우스를 바라보게 할지 나타내는 변수
	bool IsCharging;			//현재 차징 중인지 나타내는 변수
	
	
	class USkillGaugeBar* SkillGaugeBar;


};
