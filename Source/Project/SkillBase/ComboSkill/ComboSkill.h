// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/SkillBase/BaseSkill.h"
#include "ComboSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UComboSkill : public UBaseSkill
{
	GENERATED_BODY()
	
public:
	UComboSkill();

	virtual bool Use() override;
	virtual void End() override;

	//SkillComboCheck함수
	//---------------------------------------------------------
	//다음 콤보를 위한 키가 눌렸으면 다음 콤보 애니메이션 재생
	//키가 안눌렸으면 다시 idel상태로 돌아가기
	void SkillComboCheck();
	//---------------------------------------------------------

public:
	void SetComboInput(bool Enable) { ComboInput = Enable; }
	void SetCanNextCombo(bool Enable) { CanNextCombo = Enable; }

	bool GetComboInput() const { return ComboInput; }

protected:
	//현재 Combo
	int32 CurrentCombo;

	//최대 Combo
	int32 MaxCombo;

	//현재 공격키 입력이 눌렸는지 나타내는 변수
	bool ComboInput;

	//공격키 입력을 받는 시점을 나타내는 변수
	//CanNextCombo가 true인 상태에서 공격키가 눌러야 IsComboInput을 true로 바꾼다
	bool CanNextCombo;
};
