// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillArrowShower.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"
#include "TimerManager.h"
#include "Archer/Effect/ArcherArrowShowerSkillEffect.h"
#include "WorldSubSystem/EffectObjectPool.h"

UArcherSkillArrowShower::UArcherSkillArrowShower()
	: Range(700.0f), EffectTermTime(0.7), AttackLocationHeightOffset(100.f)
{
	SetCharginSpeed(1.0f);
	SetTotalChargingTime(1.0f);

	SetCoolTime(1.0f);
}

bool UArcherSkillArrowShower::Use()
{
	if (!Super::Use())
		return false;

	Archer->SetBowChargingEffect(true);
	Archer->RangeMarkOn(Range);
	Archer->SetAttackAreaMark(true);

	AArcherPlayerController* PlayerController = Cast<AArcherPlayerController>(Archer->GetController());
	if (nullptr == PlayerController)
		return false;
	PlayerController->SetAreaMarkEffectCurSkillRange(Range);

	return true;
}

void UArcherSkillArrowShower::ReleaseEffect()
{
	Archer->SetBowChargingEffect(false);
	Archer->RangeMarkOff();
	Archer->SetAttackAreaMark(false);
}

void UArcherSkillArrowShower::CreateSkillEffect()
{
	UWorld* World = nullptr;
	if (nullptr != Archer)
		World = Archer->GetWorld();

	if (nullptr != World)
	{
		UEffectObjectPool * EffectObjectPool = World->GetSubsystem<UEffectObjectPool>();
		if (EffectObjectPool)
		{
			AArcherArrowShowerSkillEffect * SkillEffect = EffectObjectPool->GetArcherArrowShowerSkillEffect();
			

			//컨트롤러에게 현재 스킬 범위 Actor의 위치를 받아서 해당 위치에 SkillEffect를 생성
			AArcherPlayerController* PlayerController = Cast<AArcherPlayerController>(Archer->GetController());
			if (nullptr == PlayerController)
				return;
		
			AttackLocation.Z += AttackLocationHeightOffset;
			FTransform SpawnTransform(AttackLocation);
			
			
			SkillEffect->SpwanNiagaraEffect(SpawnTransform);
			
		}
	}
}

void UArcherSkillArrowShower::CompleteChargingProc()
{
	//플레이어to마우스 벡터와 플레이어 앞 벡터가 이루는 각이 0도이면
	//마우스 좌표에 이펙트 생성
	//만약 플레이어의 회전 속도가 마우스 방향을 못 따라가서 각이 다르면
	//해당 거리만큼 플레이어 앞 벡터를 이동한 좌표에 이펙트를 생성
	
	AArcherPlayerController* PlayerController = Cast<AArcherPlayerController>(Archer->GetController());
	if (nullptr == PlayerController)
		return;

	FVector PlayerPos = Archer->GetActorLocation();
	FVector MousePos = PlayerController->GetMouseWorldLocation();
	FVector PlayerForwardVector = Archer->GetActorForwardVector();
	FVector PlayerToMouseVector = MousePos - PlayerPos;
	
	//PlayerForwardVector == PlayerToMouseVector
	double DorResult = FVector::DotProduct(PlayerForwardVector.GetSafeNormal(), PlayerToMouseVector.GetSafeNormal());
	if (FMath::IsNearlyEqual(DorResult, 1,FLT_EPSILON))
	{
		
	}
	else
	{
		double Length = PlayerToMouseVector.Length();
	}

	UWorld* World = nullptr;
	if(nullptr != Archer)
		World = Archer->GetWorld();

	if(nullptr != World)
		World->GetTimerManager().SetTimer(EffectCreateTimer, this, &UArcherSkillArrowShower::CreateSkillEffect, EffectTermTime, false);

	AttackLocation = PlayerController->GetAttakAreaMarkLocation();
}
