#include "SkillGaugeBar.h"
#include "Components/ProgressBar.h"
#include "SkillBase/ChargingSkill/ChargingSkill.h"

void USkillGaugeBar::SetPercent(float Percent)
{
	if (SkillGaugeBar)
	{
		CurPercent = Percent;
		SkillGaugeBar->SetPercent(Percent);
	}
}

void USkillGaugeBar::NativeConstruct()
{
	Super::NativeConstruct();

	SkillGaugeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_SkillGaugeBar")));

	SkillGaugeBar->SetPercent(0);
}

void USkillGaugeBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (nullptr == CurExcuteSkill)
		return;

	CurPercent += CurExcuteSkill->GetChargingSpeed() * InDeltaTime;
	CurPercent = FMath::Clamp(CurPercent, 0.0f, 1.0f);

	SkillGaugeBar->SetPercent(CurPercent);
}
