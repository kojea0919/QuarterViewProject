// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDeadHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerDeadHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ClickExitButton();

	void PlayFailAnimation();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UButton* ExitButton;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FailAnimation;
};
