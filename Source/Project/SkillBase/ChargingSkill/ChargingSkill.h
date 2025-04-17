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
	float ChargingSpeed;		//��¡ �ӵ�
	float TotalChargingTime;	//��ų�� ����ϴµ� �ʿ��� ��¡ �ð�
	
	bool IsLookMouse;			//���콺�� �ٶ󺸰� ���� ��Ÿ���� ����
	bool IsCharging;			//���� ��¡ ������ ��Ÿ���� ����
	
	
	class USkillGaugeBar* SkillGaugeBar;


};
