// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyPlayerController/LobbyPlayerController.h"
#include "Lobby/UI/LobbyHUD.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	static ConstructorHelpers::FClassFinder<ULobbyHUD> UI_LOBBYHUD_C(TEXT("/Game/GamePlay/Lobby/UI/UI_LobbyHUD.UI_LobbyHUD_C"));
	if (UI_LOBBYHUD_C.Succeeded())
		LobbyHUDWidgetClass = UI_LOBBYHUD_C.Class;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitHUD();
}

void ALobbyPlayerController::InitHUD()
{
	if (LobbyHUDWidgetClass)
	{
		LobbyHUD = CreateWidget<ULobbyHUD>(this, LobbyHUDWidgetClass);
		if (LobbyHUD)
		{
			LobbyHUD->AddToViewport();
		}
	}
}
