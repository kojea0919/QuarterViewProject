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

	ResultText->SetRenderScale(FVector2D(0.0f));
}

void UPlayerEndHUD::PlayTextAnimation()
{
	if (TextAnimation)
		PlayAnimation(TextAnimation);
}

//void UPlayerEndHUD::SetState(bool Dead)
//{
//	if (Dead)
//	{
//		ResultText->SetText(FText::FromString(TEXT("공략 실패")));
//	}
//	else
//	{
//		ResultText->SetText(FText::FromString(TEXT("공략 성공")));
//	}
//}

void UPlayerEndHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitButton")));
	if (ExitButton)
	{
		ExitButton->OnPressed.AddDynamic(this, &UPlayerEndHUD::ClickExitButton);
	}

	ResultText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ResultText")));

}
