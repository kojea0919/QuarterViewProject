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

	//스킬키 입력 애니메이션 실행
	void PlayUseSkillAnimation();
	void PlayFailUseSkillAnimation();

	void SetUltimateSlot() { IsUltimateSkillSlot = true; }
public:
	//해당 슬롯이 가지고 있는 스킬 사용하는 함수
	void UseSkill();

	void ReleaseSkill();

	
protected:
	virtual void NativeConstruct() override;

	//슬롯에 마우스가 들어오면 호출되는 함수
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	//슬롯에 마우스가 나가면 호출되는 함수
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	//슬롯에 마우스 버튼이 눌리면 호출되는 함수
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//드래그가 감지되면 호출되는 함수
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	//드롭되면 호출되는 함수
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void SwapSkill(USkillQuickSlot* OtherSlot);

	void SetSkillTypeImage(const class UBaseSkill* Skill);

private:
	//슬롯 배경 이미지
	//------------------------------------------
	UPROPERTY()
	class UImage* SlotImage;
	//------------------------------------------

	UPROPERTY()
	class UImage* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDragImage> DragImageWidgetClass;

	//슬롯 키를 표시할 TextBlock
	UPROPERTY()
	class UTextBlock* SlotKeyText;

	//스킬 타입을 표시할 Image
	//------------------------------------------
	UPROPERTY()
	class UImage* SkillTypeImage;

	UPROPERTY()
	class UTexture2D* ChargingSkillTypeTexture;

	UPROPERTY()
	class UTexture2D* ComboSkillTypeTexture;
	//------------------------------------------

	//CoolTime을 표시할 TextBlock
	UPROPERTY()
	class UTextBlock* RemainCoolTime;

	//CoolTime이 끝나면 실행될 효과를 위한 Image
	//UPROPERTY()
	//class UImage* SkillCoolTimeEnd;

	//CoolTime이 끝나면 실행될 효과
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SkillCoolTimeEndAnimation;

	//스킬키가 눌리고 스킬 사용이 가능한 경우 실행될 효과
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* UseSkillAnimation;

	//스킬키가 눌리고 스킬 사용이 불가능한 경우 실행될 효과
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FailUseSkillAnimation;

	//비어있는 슬롯인지 나타내는 bool변수
	bool Empty;

	//현재 슬롯에 있는 Skill
	class UBaseSkill* SlotSkill;

	bool IsUltimateSkillSlot;


};
