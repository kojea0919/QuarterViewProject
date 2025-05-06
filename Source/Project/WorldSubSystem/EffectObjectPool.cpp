// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObjectPool.h"
#include "Archer/Effect/ArcherBasicAttackArrowEffect.h"
#include "Archer/Effect/ArcherBasicAttackMuzzleEffect.h"
#include "Archer/Effect/ArcherDesperadoSkillEffect.h"
#include "Archer/Effect/ArcherMoveSkillFootDecal.h"
#include "Archer/Effect/MoveSkillFootDirt.h"
#include "Archer/Effect/ArcherSpecialAttackArrowEffect.h"
#include "Archer/Effect/ArcherBigArrowEffect.h"
#include "Archer/Effect/ArcherArrowShowerSkillEffect.h"
#include "Archer/Effect/AfterimageEffect.h"
#include "Archer/Effect/ArcherLaserEffect.h"
#include "Archer/Effect/ArcherPulseShotMuzzleEffect.h"
#include "Monster/Effect/BasicHitEffect.h"
#include "Monster/Effect/BossSawToothSkillEffect.h"
#include "Monster/Effect/BossSpawnMeteorReadyEffect.h"
#include "Monster/Effect/BossMeteorTargetAreaMarkEffect.h"
#include "Monster/Effect/BossMeteorEffect.h"


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
	InitArr(ArcherArrowShowerSkillEffectArr, 1);
	InitArr(ArcherLaserEffectArr, 1);
	InitArr(BasicHitEffectArr, 3);
	InitArr(BossSawToothSkillEffectArr, 1);
	InitArr(BossSpawnMeteorReadyEffectArr, 1);
	InitArr(BossMeteorTargetAreaMarkEffectArr, 12);
	InitArr(BossMeteorEffectArr, 12);
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

AArcherLaserEffect* UEffectObjectPool::GetArcherLaserEffect()
{
	return GetEffectObject(ArcherLaserEffectArr);
}

void UEffectObjectPool::ReturnArcherLaserEffect(AArcherLaserEffect* ReturnObj)
{
	ReturnEffectObject(ArcherLaserEffectArr, ReturnObj);
}

AArcherPulseShotMuzzleEffect* UEffectObjectPool::GetArcherPulseShotMuzzleEffect()
{
	return GetEffectObject(ArcherPulseShotMuzzleEffectArr);
}

void UEffectObjectPool::ReturnArcherPulseShotMuzzleEffect(AArcherPulseShotMuzzleEffect* ReturnObj)
{
	ReturnEffectObject(ArcherPulseShotMuzzleEffectArr, ReturnObj);
}

ABasicHitEffect* UEffectObjectPool::GetBasicHitEffect()
{
	return GetEffectObject(BasicHitEffectArr);
}

void UEffectObjectPool::ReturnBasicHitEffect(ABasicHitEffect* ReturnObj)
{
	ReturnEffectObject(BasicHitEffectArr, ReturnObj);
}

ABossSawToothSkillEffect* UEffectObjectPool::GetBossSawToothSkillEffect()
{
	return GetEffectObject(BossSawToothSkillEffectArr);
}

void UEffectObjectPool::ReturnBossSawToothSkillEffect(ABossSawToothSkillEffect* ReturnObj)
{
	ReturnEffectObject(BossSawToothSkillEffectArr, ReturnObj);
}

ABossSpawnMeteorReadyEffect* UEffectObjectPool::GetBossSpawnMeteorReadyEffect()
{
	return GetEffectObject(BossSpawnMeteorReadyEffectArr);
}

void UEffectObjectPool::ReturntBossSpawnMeteorReadyEffect(ABossSpawnMeteorReadyEffect* ReturnObj)
{
	ReturnEffectObject(BossSpawnMeteorReadyEffectArr, ReturnObj);
}

ABossMeteorTargetAreaMarkEffect* UEffectObjectPool::GetBossMeteorTargetAreaMarkEffect()
{
	return GetEffectObject(BossMeteorTargetAreaMarkEffectArr);
}

void UEffectObjectPool::ReturntBossMeteorTargetAreaMarkEffect(ABossMeteorTargetAreaMarkEffect* ReturnObj)
{
	ReturnEffectObject(BossMeteorTargetAreaMarkEffectArr, ReturnObj);
}

ABossMeteorEffect* UEffectObjectPool::GetBossMeteorEffect()
{
	return GetEffectObject(BossMeteorEffectArr);
}

void UEffectObjectPool::ReturnBossMeteorEffect(ABossMeteorEffect* ReturnObj)
{
	ReturnEffectObject(BossMeteorEffectArr, ReturnObj);
}
