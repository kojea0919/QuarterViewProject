// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObjectPool.h"
#include "Project/Archer/Effect/ArcherBasicAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherBasicAttackMuzzleEffect.h"
#include "Project/Archer/Effect/ArcherDesperadoSkillEffect.h"
#include "Project/Archer/Effect/ArcherMoveSkillFootDecal.h"
#include "Project/Archer/Effect/MoveSkillFootDirt.h"

UEffectObjectPool::UEffectObjectPool()
{
}

void UEffectObjectPool::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (nullptr != GetWorld())
	{
		GetWorld()->OnWorldBeginPlay.AddUObject(this, &UEffectObjectPool::Init);
	}
}

void UEffectObjectPool::Init()
{
	InitArr(ArcherBasicAttackArrowEffectArr, 3);
	InitArr(ArcherBasicAttackMuzzleEffectArr, 3);
	InitArr(ArcherMoveSkillFootDecalArr, 3);
	InitArr(ArcherMoveSkillFootDirtArr, 2);
	InitArr(ArcherDesperadoSkillArr, 1);
}

AArcherBasicAttackArrowEffect* UEffectObjectPool::GetArcherBasicAttackArrowEffect()
{
	return GetEffectObject(ArcherBasicAttackArrowEffectArr);
}

void UEffectObjectPool::ReturnArcherBasicAttackArrowEffect(AArcherBasicAttackArrowEffect* ReturnObj)
{
	ReturnEffectObject(ArcherBasicAttackArrowEffectArr, ReturnObj);
}

AArcherBasicAttackMuzzleEffect* UEffectObjectPool::GetArcherBasicAttackMuzzleEffect()
{
	return GetEffectObject(ArcherBasicAttackMuzzleEffectArr);
}

void UEffectObjectPool::ReturnArcherBasicAttackMuzzleEffect(AArcherBasicAttackMuzzleEffect* ReturnObj)
{
	ReturnEffectObject(ArcherBasicAttackMuzzleEffectArr, ReturnObj);
}

AArcherMoveSkillFootDecal* UEffectObjectPool::GetArcherMoveSkillFootDecal()
{
	return GetEffectObject(ArcherMoveSkillFootDecalArr);
}

void UEffectObjectPool::ReturnArcherMoveSkillFootDecal(AArcherMoveSkillFootDecal* ReturnObj)
{
	ReturnEffectObject(ArcherMoveSkillFootDecalArr, ReturnObj);
}

AMoveSkillFootDirt* UEffectObjectPool::GetMoveSkillFootDirt()
{
	return GetEffectObject(ArcherMoveSkillFootDirtArr);
}

void UEffectObjectPool::ReturnMoveSkillFootDirt(AMoveSkillFootDirt* ReturnObj)
{
	ReturnEffectObject(ArcherMoveSkillFootDirtArr, ReturnObj);
}

AArcherDesperadoSkillEffect* UEffectObjectPool::GetDesperadoSkillEffect()
{
	return GetEffectObject(ArcherDesperadoSkillArr);
}

void UEffectObjectPool::ReturnDesperadoSkillEffect(AArcherDesperadoSkillEffect* ReturnObj)
{
	ReturnEffectObject(ArcherDesperadoSkillArr, ReturnObj);
}
