// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Skill/ArcherSkillDiveShot.h"
#include "Archer/Archer.h"

UArcherSkillDiveShot::UArcherSkillDiveShot()
{
	//구형 Collision 정보 Setting
	//-----------------------------
	CollisionForwardScaleArr.Push(0);
	CollisionTypeArr.Push(ECollisionType::Sphere);
	CollisionExtentArr.Push(FVector(150.0f));
	CollisionHeightOffsetArr.Push(-90.0f);

	CurCollisionIdx = 0;
	//-----------------------------

	SkillDamage = 2444444;
}

bool UArcherSkillDiveShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);

	return true;
}