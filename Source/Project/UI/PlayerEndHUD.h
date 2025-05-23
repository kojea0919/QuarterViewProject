// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEndHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPlayerEndHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ClickExitButton();

	void PlayTextAnimation();

	//void SetState(bool Dead);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UButton* ExitButton;

	UPROPERTY()
	class UTextBlock* ResultText;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* TextAnimation;
};
