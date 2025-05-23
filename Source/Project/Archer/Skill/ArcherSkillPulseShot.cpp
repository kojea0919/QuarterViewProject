// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/Skill/ArcherSkillPulseShot.h"
#include "Archer/Archer.h"

UArcherSkillPulseShot::UArcherSkillPulseShot()
{
	NeedRotation = true;

	CollisionForwardScaleArr.Push(600);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(600.0f, 70.f, 70.0f));
	CollisionHeightOffsetArr.Push(0.0f);

	DamageTermTime = 0.05f;
	MaxCallDamageTimerNum = 12;

	SkillDamage = 7666666;
}

bool UArcherSkillPulseShot::Use()
{
	if(!Super::Use())
		return false;

	Archer->SetMoveAble(false);
	Archer->PlayCameraShake();
	Archer->PlayCameraZoomOut(600, 500);

	return true;
}
