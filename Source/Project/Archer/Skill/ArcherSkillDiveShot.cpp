// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Skill/ArcherSkillDiveShot.h"
#include "Archer/Archer.h"

bool UArcherSkillDiveShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);

	return true;
}
