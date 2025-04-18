// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillQuickSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USkillQuickSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMaterial(UMaterialInstanceDynamic* Material);

	bool IsEmpty() const { return Empty; }
	void SetEmpty(bool Enable) { Empty = Enable; }

	//Slot Skill Get Set
	//--------------------------------------
	void SetSkill(class UBaseSkill* Skill);
	class UBaseSkill* GetSkill() const { return SlotSkill; }
	//--------------------------------------

	//SlotKeyText의 Text를 SlotKey로 설정
	void SetSlotKeyText(const TCHAR* SlotKey);

	//남은 쿨타임 Text 설정함수
	//--------------------------------------
	void SetRemainCoolTimeVisible(bool Enable);	//CoolTime Text를 보여주거나 숨기는 함수
	void UpdateRemainCoolTime();				//남은 쿨타임 계산후 Text에 출력하는 함수
	//--------------------------------------

	//쿨타임 끝나는 효과 애니메이션 실행
	void PlaySkillCoolTimeEndAnimation();

	void SetUltimateSlot() { IsUltimateSkillSlot = true; }
public:
	//해당 슬롯이 가지고 있는 스킬 사용하는 함수
	void UseSkill();

	void ReleaseSkill();

	
protected:
	virtual void NativeConstruct() override;

	//슬롯에 마우스 버튼이 눌리면 호출되는 함수
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//드래그가 감지되면 호출되는 함수
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	//드롭되면 호출되는 함수
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void SwapSkill(USkillQuickSlot* OtherSlot);

private:
	UPROPERTY()
	class UImage* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDragImage> DragImageWidgetClass;

	//슬롯 키를 표시할 TextBlock
	UPROPERTY()
	class UTextBlock* SlotKeyText;

	//CoolTime을 표시할 TextBlock
	UPROPERTY()
	class UTextBlock* RemainCoolTimeText;

	//CoolTime이 끝나면 실행될 효과를 위한 Image
	UPROPERTY()
	class UImage* SkillCoolTimeEnd;

	//CoolTime이 끝나면 실행될 효과
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SkillCoolTimeEndAnimation;

	//비어있는 슬롯인지 나타내는 bool변수
	bool Empty;

	//현재 슬롯에 있는 Skill
	class UBaseSkill* SlotSkill;

	bool IsUltimateSkillSlot;
};
