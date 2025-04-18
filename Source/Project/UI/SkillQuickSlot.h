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

	//SlotKeyText�� Text�� SlotKey�� ����
	void SetSlotKeyText(const TCHAR* SlotKey);

	//���� ��Ÿ�� Text �����Լ�
	//--------------------------------------
	void SetRemainCoolTimeVisible(bool Enable);	//CoolTime Text�� �����ְų� ����� �Լ�
	void UpdateRemainCoolTime();				//���� ��Ÿ�� ����� Text�� ����ϴ� �Լ�
	//--------------------------------------

	//��Ÿ�� ������ ȿ�� �ִϸ��̼� ����
	void PlaySkillCoolTimeEndAnimation();

	void SetUltimateSlot() { IsUltimateSkillSlot = true; }
public:
	//�ش� ������ ������ �ִ� ��ų ����ϴ� �Լ�
	void UseSkill();

	void ReleaseSkill();

	
protected:
	virtual void NativeConstruct() override;

	//���Կ� ���콺 ��ư�� ������ ȣ��Ǵ� �Լ�
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//�巡�װ� �����Ǹ� ȣ��Ǵ� �Լ�
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	//��ӵǸ� ȣ��Ǵ� �Լ�
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	void SwapSkill(USkillQuickSlot* OtherSlot);

private:
	UPROPERTY()
	class UImage* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDragImage> DragImageWidgetClass;

	//���� Ű�� ǥ���� TextBlock
	UPROPERTY()
	class UTextBlock* SlotKeyText;

	//CoolTime�� ǥ���� TextBlock
	UPROPERTY()
	class UTextBlock* RemainCoolTimeText;

	//CoolTime�� ������ ����� ȿ���� ���� Image
	UPROPERTY()
	class UImage* SkillCoolTimeEnd;

	//CoolTime�� ������ ����� ȿ��
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SkillCoolTimeEndAnimation;

	//����ִ� �������� ��Ÿ���� bool����
	bool Empty;

	//���� ���Կ� �ִ� Skill
	class UBaseSkill* SlotSkill;

	bool IsUltimateSkillSlot;
};
