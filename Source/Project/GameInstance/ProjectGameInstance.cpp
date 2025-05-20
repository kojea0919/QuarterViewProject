// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Lobby/LobbyPlayerController/LobbyPlayerController.h"

void UProjectGameInstance::LoadMainLevel()
{
	UGameplayStatics::OpenLevel(this, TEXT("/Game/GamePlay/Map/MainLevel"));
}
