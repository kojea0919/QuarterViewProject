// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillGaugeBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USkillGaugeBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPercent(float Percent);

	void SetCurrentSkill(class UChargingSkill* ChargingSkill) { if (nullptr == CurExcuteSkill) CurExcuteSkill = ChargingSkill; }

	float GetPercent() const { return CurPercent; }

protected:
	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	class UProgressBar* SkillGaugeBar;

	//현재 실행 중인 Skill에 대한 포인터
	class UChargingSkill* CurExcuteSkill;

	float CurPercent;
};
