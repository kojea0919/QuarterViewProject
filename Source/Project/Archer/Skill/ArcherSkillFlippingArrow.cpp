// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillFlippingArrow.h"
#include "Project/Archer/Archer.h"

UArcherSkillFlippingArrow::UArcherSkillFlippingArrow()
{
	CurrentCombo = 0;
	MaxCombo = 3;

	ComboInput = false;
	CanNextCombo = false;
}

bool UArcherSkillFlippingArrow::Use()
{
	if (!Super::Use())
		return false;

	Archer->SetMoveAble(false);
	return true;
}
