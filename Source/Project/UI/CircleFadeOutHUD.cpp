// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CircleFadeOutHUD.h"
#include "Components/Image.h"

void UCircleFadeOutHUD::PlayCircleFadeOut()
{
	UpdateFade = true;
	CurValue = -0.7;
}

void UCircleFadeOutHUD::NativeConstruct()
{
	Super::NativeConstruct();

	FadeOutImage = Cast<UImage>(GetWidgetFromName(FName("FadeOutImage")));

	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/GamePlay/GamePlayEffect/SolarEclipse/MI_Solar_FadeOut.MI_Solar_FadeOut"));

	if (Material)
	{
		DynMaterial = UMaterialInstanceDynamic::Create(Material, this);

		DynMaterial->SetScalarParameterValue(FName("Progress"), -0.7f);

		FadeOutImage->SetBrushFromMaterial(DynMaterial);
	}

	UpdateFade = false;
	CurValue = -0.7;
}

void UCircleFadeOutHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	if (UpdateFade)
	{
		CurValue += InDeltaTime * Speed;
		if (CurValue >= 1.0f)
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		DynMaterial->SetScalarParameterValue(FName("Progress"), CurValue);
	}

}
