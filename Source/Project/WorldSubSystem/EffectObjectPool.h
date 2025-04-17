// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EffectObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UEffectObjectPool : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UEffectObjectPool();

	virtual void Initialize(FSubsystemCollectionBase& Collection);
	void Init();


public:
	class AArcherBasicAttackArrowEffect* GetArcherBasicAttackArrowEffect();
	void ReturnArcherBasicAttackArrowEffect(class AArcherBasicAttackArrowEffect* ReturnObj);

	class AArcherBasicAttackMuzzleEffect* GetArcherBasicAttackMuzzleEffect();
	void ReturnArcherBasicAttackMuzzleEffect(class AArcherBasicAttackMuzzleEffect* ReturnObj);

	class AArcherMoveSkillFootDecal* GetArcherMoveSkillFootDecal();
	void ReturnArcherMoveSkillFootDecal(class AArcherMoveSkillFootDecal* ReturnObj);

	class AMoveSkillFootDirt* GetMoveSkillFootDirt();
	void ReturnMoveSkillFootDirt(class AMoveSkillFootDirt* ReturnObj);

private:
	//Array Size Init함수
	template<typename T>
	void InitArr(TArray<T*>& Arr, uint8 InitSize);

	template<typename T>
	T* GetEffectObject(TArray<T*>& Arr);

	template<typename T>
	void ReturnEffectObject(TArray<T*>& Arr, T* ReturnObj);

private:
	UPROPERTY()
	TArray<class AArcherBasicAttackArrowEffect*> ArcherBasicAttackArrowEffectArr;

	UPROPERTY()
	TArray<class AArcherBasicAttackMuzzleEffect*> ArcherBasicAttackMuzzleEffectArr;

	UPROPERTY()
	TArray<class AArcherMoveSkillFootDecal*> ArcherMoveSkillFootDecalArr;

	UPROPERTY()
	TArray<class AMoveSkillFootDirt*> ArcherMoveSkillFootDirtArr;
};


template<typename T>
inline void UEffectObjectPool::InitArr(TArray<T*>& Arr, uint8 InitSize)
{
	if (GetWorld() == nullptr)
		return;
	//InitSize만큼 초기화
	//-----------------------------------------
	for (uint8 idx = 0; idx < InitSize; ++idx)
	{
		T* Obj = GetWorld()->SpawnActor<T>(T::StaticClass());
		if (nullptr == Obj)
			return;

		Obj->SetEffectEnable(false);
		Arr.Add(Obj);
	}
	//-----------------------------------------
}

template<typename T>
inline T* UEffectObjectPool::GetEffectObject(TArray<T*>& Arr)
{
	if (nullptr == GetWorld())
		return nullptr;

	T* Obj;
	//배열이 비어 있으면 새로운 객체 생성
	if (0 == Arr.Num())
	{
		Obj = GetWorld()->SpawnActor<T>(T::StaticClass());
	}
	else
	{
		Obj = Arr.Pop();
		if (nullptr == Obj)
			return nullptr;
	}

	Obj->SetTickEnable(true);
	Obj->SetEffectEnable(true);

	return Obj;
}

template<typename T>
inline void UEffectObjectPool::ReturnEffectObject(TArray<T*>& Arr, T* ReturnObj)
{
	if (nullptr == ReturnObj)
		return;

	ReturnObj->SetEffectEnable(false);
	ReturnObj->SetTickEnable(false);

	Arr.Add(ReturnObj);
}