// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageText.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UDamageText::SetDamageText(float Damage)
{
	if (DamageText)
		DamageText->SetText(FText::AsNumber(Damage));
}

void UDamageText::PlayBasicDamageTextAnimation()
{
	if (BasicDamageTextAnimation)
		PlayAnimation(BasicDamageTextAnimation);
}

void UDamageText::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = nullptr;

	DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_DamageText")));

}

void UDamageText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerController)
	{
		FVector2D ScreenPos;
		UGameplayStatics::ProjectWorldToScreen(PlayerController, OwnerLocation, ScreenPos);
		SetPositionInViewport(ScreenPos);
	}

	if (DamageText)
	{
		if (FMath::IsNearlyEqual(DamageText->GetRenderTransform().Scale.X, 1, FLT_EPSILON))
		{
			RemoveFromParent();
		}
	}
}
