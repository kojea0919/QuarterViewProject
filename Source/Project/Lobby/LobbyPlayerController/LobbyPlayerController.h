// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPlayerController();

	virtual void BeginPlay() override;

private:
	void InitHUD();

private:
	//Lobby HUD
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class ULobbyHUD> LobbyHUDWidgetClass;

	class ULobbyHUD* LobbyHUD;
	//-------------------------------------------------
	
};
