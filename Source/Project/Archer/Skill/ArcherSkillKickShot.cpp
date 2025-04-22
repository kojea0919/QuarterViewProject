// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillKickShot.h"
#include "Project/Archer/Archer.h"

bool UArcherSkillKickShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);

	return true;
}
