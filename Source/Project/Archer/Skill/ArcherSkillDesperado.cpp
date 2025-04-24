// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillDesperado.h"
#include "Archer/Archer.h"

bool UArcherSkillDesperado::Use()
{
	if(!Super::Use())
		return false;

	Archer->GetCharacterMovement()->bOrientRotationToMovement = false;

	return true;
}