// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillArrowShower.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/ArcherPlayerController.h"

UArcherSkillArrowShower::UArcherSkillArrowShower()
{
	SetCharginSpeed(1.0f);
	SetTotalChargingTime(1.0f);
}

bool UArcherSkillArrowShower::Use()
{
	if (!Super::Use())
		return false;

	Archer->SetBowChargingEffect(true);

	return true;
}

void UArcherSkillArrowShower::ReleaseEffect()
{
	Archer->SetBowChargingEffect(false);
}
