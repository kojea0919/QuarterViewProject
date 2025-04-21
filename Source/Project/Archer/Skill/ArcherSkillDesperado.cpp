// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillDesperado.h"
#include "Project/Archer/Archer.h"

bool UArcherSkillDesperado::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetLookMouseDirection(false);
	return true;
}