// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerProgressBar.h"
#include "Components/ProgressBar.h"

void UPlayerProgressBar::SetPlayerCurrentHPRate(float Rate)
{
	if (PlayerHPBar)
	{
		PlayerHPBar->SetPercent(Rate);
	}
}

void UPlayerProgressBar::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PlayerHPBar")));
}
