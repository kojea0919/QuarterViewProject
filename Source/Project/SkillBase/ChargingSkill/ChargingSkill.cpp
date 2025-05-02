// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingSkill.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"
#include "UI/SkillGaugeBar.h"

UChargingSkill::UChargingSkill()
	:  ChargingSpeed(0.0f), TotalChargingTime(0.0f), IsLookMouse(true),
	IsCharging(false),IsCanCharging(true), SkillGaugeBar(nullptr)
{
	SkillType = ESkillType::Charging;
}

bool UChargingSkill::Use()
{
	//BaseSkill의 Use함수 호출
	//Skill사용이 불가능한 상황이라면(다른 스킬 사용중) fasle return
	if (!Super::Use())
	{
		return false;
	}

	//if (!IsCanCharging)
	//	return false;

	//스킬 게이지바 출력
	if (SkillGaugeBar)
	{
		SkillGaugeBar->SetCurrentSkill(this);
		SkillGaugeBar->SetVisibility(ESlateVisibility::Visible);
		SkillGaugeBar->SetPercent(0.0f);
	}
	
	//이동 불가능 상태로 만들고 현재 이동 멈추기
	//------------------------------------------------------
	if (nullptr == Archer)
		return false;

	//플레이어 마우스 방향으로 회전시키는 함수 호출
	if (IsLookMouse)
		Archer->SetLookMouseDirection(true);
	
	Archer->SetMoveAble(false);

	AArcherPlayerController* ArcherPlayerController = Cast<AArcherPlayerController>(Archer->GetController());
	if (nullptr != ArcherPlayerController)
		ArcherPlayerController->StopMovement();
	//------------------------------------------------------

	IsCharging = true;
	//IsCanCharging = false;

	return true;
}

void UChargingSkill::ReleaseSkill()
{
	bool IsFullCharging = SkillGaugeBar->GetPercent() >= 1.0f ? true : false;
	if (IsFullCharging)
	{
		ResumeMontage();
		CompleteChargingProc();
	}
	else
	{
		StopMontage();
		Archer->SetMoveAble(true);
	}
	
	ResetSkillState();
}

void UChargingSkill::End()
{
	Super::End();

	ResetSkillState();

	IsCharging = false;
	//IsCanCharging = true;
}

void UChargingSkill::ResetSkillState()
{
	//쿨타임 시작
	StartCoolDown();

	//사용한 Charging 이펙트 제거
	ReleaseEffect();	

	//마우스 바라보게 하는 기능 Off
	if (Archer)
	{
		Archer->SetLookMouseDirection(false);
		Archer->SetUseSkill(false);
	}

	//UI끄기
	if (SkillGaugeBar)
	{
		SkillGaugeBar->SetVisibility(ESlateVisibility::Hidden);
		SkillGaugeBar->SetPercent(0.0f);
	}
}
