// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillDesperado.h"
#include "Archer/Archer.h"

UArcherSkillDesperado::UArcherSkillDesperado()
{
	//구형 Collision 정보 Setting
	//-----------------------------
	CollisionForwardScaleArr.Push(0);
	CollisionTypeArr.Push(ECollisionType::Sphere);
	CollisionExtentArr.Push(FVector(150.0f));
	CollisionHeightOffsetArr.Push(-90.0f);

	CurCollisionIdx = 0;
	//-----------------------------
}

bool UArcherSkillDesperado::Use()
{
	if(!Super::Use())
		return false;

	Archer->GetCharacterMovement()->bOrientRotationToMovement = false;

	return true;
}