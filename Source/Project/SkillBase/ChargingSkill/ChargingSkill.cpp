// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingSkill.h"
#include "../../Archer/Archer.h"
#include "../../Archer/ArcherPlayerController.h"

UChargingSkill::UChargingSkill()
	: ChargingSpeed(0.0f), TotalChargingTime(0.0f), IsLookMouse(true),
	IsCharging(false), SkillGaugeBar(nullptr)
{
}

bool UChargingSkill::Use()
{
	//BaseSkill의 Use함수 호출
	//Skill사용이 불가능한 상황이라면(다른 스킬 사용중) fasle return
	if (!Super::Use())
		return false;
	
	//스킬 게이지바 출력


	//플레이어 마우스 방향으로 회전시키는 함수 호출
	//if(IsLookMouse)
	
	//이동 불가능 상태로 만들고 현재 이동 멈추기
	//------------------------------------------------------
	if (nullptr == Archer)
		return false;
	
	Archer->SetMoveAble(false);

	AArcherPlayerController* ArcherPlayerController = Cast<AArcherPlayerController>(Archer->GetController());
	if (nullptr != ArcherPlayerController)
		ArcherPlayerController->StopMovement();
	//------------------------------------------------------

	IsCharging = true;

	return true;
}

void UChargingSkill::ReleaseSkill()
{
	//ChargingSkill은 스킬키를 떼면 플레이어의 차징 상태를 확인해 전부 채웠으면
	//애니메이션을 계속 재생하고 부족하면 애니메이션을 멈춘다.

	if (!IsCharging)
		return;

	/*bool IsFullCharging;
	if (IsFullCharging)
	{
		ResumeMontage();
	}
	else
	{
		StopMontage();
		Archer->SetMoveAble(true);
	}*/
	
	ResetSkillState();
}

void UChargingSkill::End()
{
	Super::End();

	ResetSkillState();
}

void UChargingSkill::ResetSkillState()
{
	//쿨타임 시작
	StartCoolDown();

	//사용한 Charging 이펙트 제거
	ReleaseEffect();	

	//마우스 바라보게 하는 기능 Off
	if (Archer)
		Archer->SetLookMouseDirection(false);

	//UI끄기

	IsCharging = false;
}
