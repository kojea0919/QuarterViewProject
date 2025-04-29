// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ArcherInteractionUI.h"

void UArcherInteractionUI::PlayScaleUpAnimation()
{
	if (ScaleUp)
		PlayAnimation(ScaleUp);
}

void UArcherInteractionUI::PlayScaleDownAnimation()
{
	if (ScaleDown)
		PlayAnimation(ScaleDown);
}
