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
	//BaseSkill�� Use�Լ� ȣ��
	//Skill����� �Ұ����� ��Ȳ�̶��(�ٸ� ��ų �����) fasle return
	if (!Super::Use())
		return false;
	
	//��ų �������� ���


	//�÷��̾� ���콺 �������� ȸ����Ű�� �Լ� ȣ��
	//if(IsLookMouse)
	
	//�̵� �Ұ��� ���·� ����� ���� �̵� ���߱�
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
	//ChargingSkill�� ��ųŰ�� ���� �÷��̾��� ��¡ ���¸� Ȯ���� ���� ä������
	//�ִϸ��̼��� ��� ����ϰ� �����ϸ� �ִϸ��̼��� �����.

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
	//��Ÿ�� ����
	StartCoolDown();

	//����� Charging ����Ʈ ����
	ReleaseEffect();	

	//���콺 �ٶ󺸰� �ϴ� ��� Off
	if (Archer)
		Archer->SetLookMouseDirection(false);

	//UI����

	IsCharging = false;
}
