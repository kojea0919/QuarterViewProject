// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherSkillArrowShower.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/ArcherPlayerController.h"

UArcherSkillArrowShower::UArcherSkillArrowShower()
	: Range(700.0f)
{
	SetCharginSpeed(1.0f);
	SetTotalChargingTime(1.0f);
}

bool UArcherSkillArrowShower::Use()
{
	if (!Super::Use())
		return false;

	Archer->SetBowChargingEffect(true);
	Archer->RangeMarkOn(Range);
	Archer->SetAttackAreaMark(true);

	return true;
}

void UArcherSkillArrowShower::ReleaseEffect()
{
	Archer->SetBowChargingEffect(false);
	Archer->RangeMarkOff();
	Archer->SetAttackAreaMark(false);
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

}
