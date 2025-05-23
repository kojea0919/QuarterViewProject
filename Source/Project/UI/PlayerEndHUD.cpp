// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerEndHUD.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Archer/ArcherPlayerController.h"

void UPlayerEndHUD::ClickExitButton()
{
	AArcherPlayerController * PlayerController = GetWorld()->GetFirstPlayerController<AArcherPlayerController>();
	if (PlayerController)
	{
		PlayerController->ResetPlayerAndBoss();
	}

	FailText->SetRenderScale(FVector2D(0.0f));
	SuccessText->SetRenderScale(FVector2D(0.0f));
}

void UPlayerEndHUD::PlayTextAnimation()
{
	if (IsDead && FailAnimation)
	{	
		PlayAnimation(FailAnimation);
	}
	else if (SuccessAnimation)
	{
		PlayAnimation(SuccessAnimation);
	}
}

void UPlayerEndHUD::NativeConstruct()
{
	Super::NativeConstruct();

	IsDead = false;

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	if (ExitButton)
	{
		ExitButton->OnPressed.AddDynamic(this, &UPlayerEndHUD::ClickExitButton);
	}

	FailText = Cast<UTextBlock>(GetWidgetFromName(TEXT("FailText")));

	SuccessText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SuccessText")));

}
