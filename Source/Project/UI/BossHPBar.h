// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHPBar.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossHPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitBossHP();
	void SetBossMaxHP(float HP) { BossMaxHP = HP; OneLineHPAmount = BossMaxHP / (float)HPLineCount; }
	void SetBossCurrentHP(float newHP);

	void SetBossHPLineCount(int Count) { HPLineCount = Count;}

protected:
	virtual void NativeConstruct() override;

private:
	//------------------------------------
	UPROPERTY()
	class UProgressBar* BossHPBar;

	UPROPERTY()
	class UTextBlock* BossHPText;

	UPROPERTY()
	class UImage* NextHPBar;

	UPROPERTY()
	class UImage* BossHPLine;

	float BossMaxHP;
	//------------------------------------

	int HPLineCount;
	float OneLineHPAmount;		//1ÁÙ´ç HP¾ç
	int CurHPLine;

	TArray<FLinearColor> HpBarColor;
	int CurColorIdx;

	const int LineLeft = 117;
	const int LineRight = 1008;
	const int Distance = 891;

	bool BossIsDead = false;


	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BossHPLineAnimation;
};
