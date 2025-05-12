// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossClear.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBossClear : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ClickExitMapButton();

private:
	UPROPERTY()
	class UButton* ExitMapButton;

};
