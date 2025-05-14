// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossHPBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UBossHPBar::InitBossHP()
{
	BossHPBar->SetPercent(1.0f);
	FString HPStr = FString::FromInt(BossMaxHP);
	HPStr += TEXT(" / ");
	HPStr += FString::FromInt(BossMaxHP);

	BossHPText->SetText(FText::FromString(HPStr));

	CurHPLine = HPLineCount;

	NextHPBar->SetVisibility(ESlateVisibility::Visible);

	BossIsDead = false;
}

void UBossHPBar::SetBossCurrentHP(float newHP)
{
	if (BossIsDead)
		return;

	if (BossHPBar && BossHPText && NextHPBar)
	{
		float OneLineHP = (int)newHP % (int)OneLineHPAmount;
		float LineCount = (int)newHP / (int)OneLineHPAmount;


		float CurLineRate;
		if (OneLineHP == 0 && newHP != 0)
		{
			BossHPBar->SetPercent(1.0f);
			CurLineRate = 1.0f;
		}
		else if (newHP <= 0)
		{
			newHP = 0;
			BossHPBar->SetPercent(0.0f);
			CurLineRate = 0.0f;
			NextHPBar->SetVisibility(ESlateVisibility::Hidden);
			BossIsDead = true;
		}
		else
		{
			CurLineRate = OneLineHP / OneLineHPAmount;
			BossHPBar->SetPercent(OneLineHP / OneLineHPAmount);
		}

		//줄이 바뀐 경우 체력바 색상 바꿔주기
		if (LineCount + 1 < CurHPLine)
		{
			CurHPLine = LineCount;
			NextHPBar->SetColorAndOpacity(HpBarColor[CurColorIdx]);

			CurColorIdx = (CurColorIdx + 1) % HpBarColor.Num();
			BossHPBar->SetFillColorAndOpacity(HpBarColor[CurColorIdx]);
		}

		int NewTransform = LineLeft + (Distance) * CurLineRate;
		FWidgetTransform LineTransform = BossHPLine->GetRenderTransform();
		LineTransform.Translation = FVector2D(NewTransform, LineTransform.Translation.Y);
		BossHPLine->SetRenderTransform(LineTransform);


		FString HPStr = FString::FromInt(newHP);
		HPStr += TEXT(" / ");
		HPStr += FString::FromInt(BossMaxHP);

		BossHPText->SetText(FText::FromString(HPStr));
	}
}

void UBossHPBar::NativeConstruct()
{
	Super::NativeConstruct();

	HPLineCount = 10;
	//보스 체력 UI
	//---------------------------------------------------------------
	BossHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHPBar")));

	BossHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BossHPText")));

	NextHPBar = Cast<UImage>(GetWidgetFromName(TEXT("BossNextHPBar")));

	BossHPLine = Cast<UImage>(GetWidgetFromName(TEXT("BossHPLine")));
	//---------------------------------------------------------------

	HpBarColor.Add(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	HpBarColor.Add(FLinearColor(1.0f, 0.0f, 1.0f, 1.0f));
	CurColorIdx = 0;
}
