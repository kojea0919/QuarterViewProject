// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArcherInteractionUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UArcherInteractionUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void PlayScaleUpAnimation();
	void PlayScaleDownAnimation();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient) 
	UWidgetAnimation* ScaleUp;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ScaleDown;
};