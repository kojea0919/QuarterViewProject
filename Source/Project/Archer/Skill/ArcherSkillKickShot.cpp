// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillKickShot.h"
#include "Archer/Archer.h"

UArcherSkillKickShot::UArcherSkillKickShot()
{
	NeedRotation = true;

	CollisionForwardScaleArr.Push(160);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(100.0f,50.f,50.f));
	CollisionHeightOffsetArr.Push(0.0f);

	CollisionForwardScaleArr.Push(400);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(400.0f,70.f,70.0f));
	CollisionHeightOffsetArr.Push(0.0f);

	CurCollisionIdx = 0;

	SkillDamage = 4354354;
}

bool UArcherSkillKickShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);

	return true;
}

void UArcherSkillKickShot::CheckEnemyOverlap()
{
	Super::CheckEnemyOverlap();

	CurCollisionIdx = (CurCollisionIdx + 1) % 2;
}
