// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillQuickSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragImage.h"
#include "SkillImageDragDropOperation.h"
#include "Project/SkillBase/BaseSkill.h"

void USkillQuickSlot::SetMaterial(UMaterialInstanceDynamic* Material)
{
	//SkillImage->SetBrushFromMaterial(Material);
}

void USkillQuickSlot::SetSkill(UBaseSkill* Skill)
{
	if (Skill)
	{
		SlotSkill = Skill;

		SetMaterial(SlotSkill->GetUIMaterial());
		Empty = false;
	}
}

void USkillQuickSlot::SetSlotKeyText(const TCHAR* SlotKey)
{
	if (SlotKeyText)
		SlotKeyText->SetText(FText::FromString(SlotKey));
}

void USkillQuickSlot::SetRemainCoolTimeVisible(bool Enable)
{
	/*if (RemainCoolTimeText)
	{
		if (Enable)
		{
			RemainCoolTimeText->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			RemainCoolTimeText->SetVisibility(ESlateVisibility::Hidden);
		}
	}*/
}

void USkillQuickSlot::UpdateRemainCoolTime()
{
	//if (RemainCoolTimeText)
	//{
	//	//��ų�� ���� ���� ��Ÿ�� ���
	//	float RemainCoolTime = SlotSkill->GetRemainCoolTime();

	//	//���� �κа� �Ҽ� �κ� �и�
	//	uint8 IntegerPart = RemainCoolTime;
	//	uint8 DecimalPart = (RemainCoolTime - IntegerPart) * 10;

	//	FString RemainTimeString = FString::Printf(TEXT("%d.%d"), IntegerPart, DecimalPart);

	//	RemainCoolTimeText->SetText(FText::FromString(RemainTimeString));
	//}
}

void USkillQuickSlot::PlaySkillCoolTimeEndAnimation()
{
	//if (SkillCoolTimeEndAnimation)
	//	PlayAnimation(SkillCoolTimeEndAnimation);
}

void USkillQuickSlot::UseSkill()
{
	if (SlotSkill && !SlotSkill->IsCoolDownActive())
	{
		SlotSkill->Use();
	}
}

void USkillQuickSlot::ReleaseSkill()
{
	if (SlotSkill)
		SlotSkill->ReleaseSkill();
}

void USkillQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	Empty = true;

	//RemainCoolTimeText = Cast<UTextBlock>(GetWidgetFromName(FName("Text_RemainCoolTime")));
	//SkillCoolTimeEnd = Cast<UImage>(GetWidgetFromName(FName("Img_SkillCoolTimeEnd")));
	SlotBackGround = Cast<UButton>(GetWidgetFromName(FName("BT_SlotBackGround")));
	SkillImage = Cast<UImage>(GetWidgetFromName(FName("Img_SkillImage")));
	SlotKeyText = Cast<UTextBlock>(GetWidgetFromName(FName("Text_SlotKey")));
}

FReply USkillQuickSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//���� ������ ����ִ� ��쿡�� return
	if (Empty)
		return FReply::Unhandled();

	// ���� ���콺 ��ư�� ������ ���� ó��
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

		return ReplyResult.NativeReply;
	}
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void USkillQuickSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragImage* DragImage = CreateWidget<UDragImage>(GetOwningPlayer(), DragImageWidgetClass);

	//Texture ����
	//-------------------------------------------------------------------------------
	//UMaterialInstanceDynamic* SkillMaterial = Cast<UMaterialInstanceDynamic>(SkillImage->GetBrush().GetResourceObject());
	//DragImage->SetMaterial(SkillMaterial);
	//-------------------------------------------------------------------------------

	USkillImageDragDropOperation* DragDrop = NewObject<USkillImageDragDropOperation>(DragImage);
	OutOperation = DragDrop;
	DragDrop->DefaultDragVisual = DragImage;
	DragDrop->SetDragObject(this);
}

bool USkillQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillImageDragDropOperation* DragDropOperation = Cast<USkillImageDragDropOperation>(InOperation);
	USkillQuickSlot* DragObject = DragDropOperation->GetDragObject();


	UBaseSkill* DragSkill = DragObject->SlotSkill;

	//�� ���Կ� ��ų�� ��� �ִ� ���
	if (DragSkill && SlotSkill)
	{
		//���Կ� �ִ� ��ų�� ���� ��Ÿ�� ���̸� Swap�۾� pass
		//-------------------------------------------------------------------
		if (DragSkill->IsCoolDownActive() || SlotSkill && SlotSkill->IsCoolDownActive())
			return false;
		//-------------------------------------------------------------------

		//�ñر�� �Ϲ� ��ų�� Swap�۾� pass
		bool DragSkillIsUltimate = DragSkill->GetIsUltimateSkill();
		bool CurSkillIsUltimate = SlotSkill->GetIsUltimateSkill();

		if (DragSkillIsUltimate || CurSkillIsUltimate)
			return false;
	}
	else if (DragSkill)
	{
		if (DragSkill->IsCoolDownActive())
			return false;

		//�巡���� ��ų�� �ñر� �̰ų� �������� ������ �ñر�� �����̸� Swap�۾� pass
		bool DragSkillIsUltimate = DragSkill->GetIsUltimateSkill();
		if (DragSkillIsUltimate || IsUltimateSkillSlot)
			return false;
	}

	//Skill Swap�۾�
	//-------------------------------------------------------------------------------
	SwapSkill(DragObject);
	//-------------------------------------------------------------------------------

	return true;
}

void USkillQuickSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//���� ���Կ� �ִ� ��ų�� ��Ÿ���̸� CoolDownó��
	if (nullptr != SlotSkill && SlotSkill->IsCoolDownActive())
	{
		//Material Update
		SlotSkill->UpdateCoolDownEffect(InDeltaTime);

		//CoolTeim Text Update
		UpdateRemainCoolTime();
	}
}


void USkillQuickSlot::SwapSkill(USkillQuickSlot* OtherSlot)
{
	//if (IsValid(OtherSlot))
	//{
	//	//Material �ٲٱ�
	//	//---------------------------------------------------------------------------
	//	UMaterialInstanceDynamic* ThisMaterial = Cast<UMaterialInstanceDynamic>(SkillImage->GetBrush().GetResourceObject());
	//	UMaterialInstanceDynamic* OtherMaterial = Cast<UMaterialInstanceDynamic>(OtherSlot->SkillImage->GetBrush().GetResourceObject());

	//	OtherSlot->SetMaterial(ThisMaterial);
	//	SetMaterial(OtherMaterial);
	//	//---------------------------------------------------------------------------

	//	//SkillSlot�ٲٱ�
	//	//---------------------------------------------------------------------------
	//	UBaseSkill* OtherSkill = OtherSlot->SlotSkill;
	//	if (OtherSkill)
	//		OtherSkill->SetQuickSlot(this);
	//	if (SlotSkill)
	//		SlotSkill->SetQuickSlot(OtherSlot);
	//	//---------------------------------------------------------------------------

	//	//Skill�ٲٱ�
	//	//---------------------------------------------------------------------------
	//	OtherSlot->SlotSkill = SlotSkill;
	//	SlotSkill = OtherSkill;
	//	//---------------------------------------------------------------------------

	//	//Empty�ٲٱ�
	//	//---------------------------------------------------------------------------
	//	bool OtherIsEmpty = OtherSlot->Empty;
	//	OtherSlot->Empty = Empty;
	//	Empty = OtherIsEmpty;
	//	//---------------------------------------------------------------------------
	//}
}
