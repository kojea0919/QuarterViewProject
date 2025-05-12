// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossClear.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UBossClear::NativeConstruct()
{
	Super::NativeConstruct();

	ExitMapButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitMapButton")));
	if (ExitMapButton)
		ExitMapButton->OnClicked.AddDynamic(this, &UBossClear::ClickExitMapButton);
}

void UBossClear::ClickExitMapButton()
{
	UGameplayStatics::OpenLevel(this, TEXT("/Game/GamePlay/Map/Lobby"));
}
