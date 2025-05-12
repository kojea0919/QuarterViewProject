// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ULobbyHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ClickGameStartButton();

private:
	UPROPERTY()
	class UButton* GameStartButton;

};
