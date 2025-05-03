// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillFlippingArrow.h"
#include "Archer/Archer.h"

UArcherSkillFlippingArrow::UArcherSkillFlippingArrow()
{
	CurrentCombo = 0;
	MaxCombo = 3;

	ComboInput = false;
	CanNextCombo = false;

	CollisionForwardScaleArr.Push(600);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(600.0f, 40.f, 70.0f));
	CollisionHeightOffsetArr.Push(0.0f);

	CollisionForwardScaleArr.Push(600);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(600.0f, 70.f, 70.0f));
	CollisionHeightOffsetArr.Push(0.0f);

	CollisionForwardScaleArr.Push(600);
	CollisionTypeArr.Push(ECollisionType::Box);
	CollisionExtentArr.Push(FVector(600.0f, 100.f, 70.0f));
	CollisionHeightOffsetArr.Push(0.0f);

	CurCollisionIdx = 0;

}

bool UArcherSkillFlippingArrow::Use()
{
	if (!Super::Use())
		return false;

	Archer->SetMoveAble(false);
	return true;
}

void UArcherSkillFlippingArrow::CheckEnemyOverlap()
{
	Super::CheckEnemyOverlap();

	CurCollisionIdx = (CurCollisionIdx + 1) % MaxCombo;
}
