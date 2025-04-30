// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Skill/ArcherSkillPulseShot.h"
#include "Archer/Archer.h"

bool UArcherSkillPulseShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);

	return true;
}
