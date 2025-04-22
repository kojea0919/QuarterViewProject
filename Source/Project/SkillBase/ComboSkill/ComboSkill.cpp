// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboSkill.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/Animation/ArcherAnimInstance.h"

UComboSkill::UComboSkill()
	: CurrentCombo(0), MaxCombo(0), ComboInput(false), CanNextCombo(false)
{
}

bool UComboSkill::Use()
{
	//Montage가 재생 중인 상태면 ComboInput만 true로 바꾸고 return
	if (IsPlayingMontage() && Archer->GetUseSkill())
	{
		if (CanNextCombo)
		{
			ComboInput = true;
		}

		return true;
	}

	//처음 콤보가 실행되는 경우
	if (0 == CurrentCombo)
	{
		if (!Super::Use())
			return false;

		AnimInstance->SetCurExcuteComboSkill(this);
		//AnimInstance->ComboSkillEndDelegate();
		++CurrentCombo;
		return true;
	}

	Archer->SetMoveAble(false);

	return true;
}

void UComboSkill::End()
{
	Super::End();

	//입력키가 안 눌려진 상태로 바꾸기
	ComboInput = false;

	//캐릭터를 이동 가능한 상태로 바꾸기
	if (Archer)
		Archer->SetMoveAble(true);

	//콤보 초기 상태로 바꾸기
	CurrentCombo = 0;
	CanNextCombo = false;

	//쿨다운 시작
	StartCoolDown();
}

void UComboSkill::SkillComboCheck()
{
	//콤보 키가 안 눌렸으면 이동 가능한 상태로 만들고 다음 몽타주 재생 X
	if (!ComboInput)
	{
		Archer->SetMoveAble(true);
		StopMontage();
	}
	//콤보 키가 눌렸으면 다음 콤보를 계산해서 해당 Section 재생
	else if (nullptr != AnimInstance)
	{
		CurrentCombo = (CurrentCombo + 1) % (MaxCombo + 1);

		//PlaySkillMontageSection(CurrentCombo);

		ComboInput = false;
		CanNextCombo = false;
	}
}
