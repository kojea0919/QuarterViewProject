// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObjectPool.h"
#include "Project/Archer/Effect/ArcherBasicAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherBasicAttackMuzzleEffect.h"
#include "Project/Archer/Effect/ArcherDesperadoSkillEffect.h"
#include "Project/Archer/Effect/ArcherMoveSkillFootDecal.h"
#include "Project/Archer/Effect/MoveSkillFootDirt.h"
#include "Project/Archer/Effect/ArcherSpecialAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherBigArrowEffect.h"
#include "Project/Archer/Effect/ArcherArrowShowerSkillEffect.h"
#include "Project/Archer/Effect/AfterimageEffect.h"

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
	InitArr(ArcherSpecialAttackArrowEffectArr, 1);
	InitArr(ArcherBigArrowEffectArr, 3);
	InitArr(AfterimageEffectArr, 10);
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

AArcherSpecialAttackArrowEffect* UEffectObjectPool::GetArcherSpecialAttackArrowEffect()
{
	return GetEffectObject(ArcherSpecialAttackArrowEffectArr);
}

void UEffectObjectPool::ReturnArcherSpecialAttackArrowEffect(AArcherSpecialAttackArrowEffect* ReturnObj)
{
	ReturnEffectObject(ArcherSpecialAttackArrowEffectArr, ReturnObj);
}

AArcherBigArrowEffect* UEffectObjectPool::GetArcherBigArrowEffect()
{
	return GetEffectObject(ArcherBigArrowEffectArr);
}

void UEffectObjectPool::ReturnArcherBigArrowEffect(AArcherBigArrowEffect* ReturnObj)
{
	ReturnEffectObject(ArcherBigArrowEffectArr, ReturnObj);
}

AAfterimageEffect* UEffectObjectPool::GetAfterimageEffect()
{
	return GetEffectObject(AfterimageEffectArr);
}

void UEffectObjectPool::ReturnAfterimageEffect(AAfterimageEffect* ReturnObj)
{
	ReturnEffectObject(AfterimageEffectArr, ReturnObj);
}

AArcherArrowShowerSkillEffect* UEffectObjectPool::GetArcherArrowShowerSkillEffect()
{
	return GetEffectObject(ArcherArrowShowerSkillEffectArr);
}

void UEffectObjectPool::ReturnArcherArrowShowerSkillEffect(AArcherArrowShowerSkillEffect* ReturnObj)
{
	ReturnEffectObject(ArcherArrowShowerSkillEffectArr, ReturnObj);
}
