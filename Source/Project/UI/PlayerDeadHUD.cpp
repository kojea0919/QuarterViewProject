// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeadHUD.h"
#include "Components/Button.h"
#include "Archer/ArcherPlayerController.h"

void UPlayerDeadHUD::ClickExitButton()
{
	AArcherPlayerController * PlayerController = GetWorld()->GetFirstPlayerController<AArcherPlayerController>();
	if (PlayerController)
	{
		PlayerController->ResetPlayerAndBoss();
	}
}

void UPlayerDeadHUD::PlayFailAnimation()
{
	if (FailAnimation)
		PlayAnimation(FailAnimation);
}

void UPlayerDeadHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	if (ExitButton)
	{
		ExitButton->OnPressed.AddDynamic(this, &UPlayerDeadHUD::ClickExitButton);
	}
}
