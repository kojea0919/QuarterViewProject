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
	//	//스킬로 부터 남은 쿨타임 계산
	//	float RemainCoolTime = SlotSkill->GetRemainCoolTime();

	//	//정수 부분과 소수 부분 분리
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
	//현재 슬롯이 비어있는 경우에는 return
	if (Empty)
		return FReply::Unhandled();

	// 왼쪽 마우스 버튼이 눌렸을 때의 처리
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

	//Texture 복사
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

	//두 슬롯에 스킬이 모두 있는 경우
	if (DragSkill && SlotSkill)
	{
		//슬롯에 있는 스킬이 아직 쿨타임 중이면 Swap작업 pass
		//-------------------------------------------------------------------
		if (DragSkill->IsCoolDownActive() || SlotSkill && SlotSkill->IsCoolDownActive())
			return false;
		//-------------------------------------------------------------------

		//궁극기와 일반 스킬은 Swap작업 pass
		bool DragSkillIsUltimate = DragSkill->GetIsUltimateSkill();
		bool CurSkillIsUltimate = SlotSkill->GetIsUltimateSkill();

		if (DragSkillIsUltimate || CurSkillIsUltimate)
			return false;
	}
	else if (DragSkill)
	{
		if (DragSkill->IsCoolDownActive())
			return false;

		//드래그한 스킬이 궁극기 이거나 놓으려는 슬롯이 궁극기용 슬롯이면 Swap작업 pass
		bool DragSkillIsUltimate = DragSkill->GetIsUltimateSkill();
		if (DragSkillIsUltimate || IsUltimateSkillSlot)
			return false;
	}

	//Skill Swap작업
	//-------------------------------------------------------------------------------
	SwapSkill(DragObject);
	//-------------------------------------------------------------------------------

	return true;
}

void USkillQuickSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//현재 슬롯에 있는 스킬이 쿨타임이면 CoolDown처리
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
	//	//Material 바꾸기
	//	//---------------------------------------------------------------------------
	//	UMaterialInstanceDynamic* ThisMaterial = Cast<UMaterialInstanceDynamic>(SkillImage->GetBrush().GetResourceObject());
	//	UMaterialInstanceDynamic* OtherMaterial = Cast<UMaterialInstanceDynamic>(OtherSlot->SkillImage->GetBrush().GetResourceObject());

	//	OtherSlot->SetMaterial(ThisMaterial);
	//	SetMaterial(OtherMaterial);
	//	//---------------------------------------------------------------------------

	//	//SkillSlot바꾸기
	//	//---------------------------------------------------------------------------
	//	UBaseSkill* OtherSkill = OtherSlot->SlotSkill;
	//	if (OtherSkill)
	//		OtherSkill->SetQuickSlot(this);
	//	if (SlotSkill)
	//		SlotSkill->SetQuickSlot(OtherSlot);
	//	//---------------------------------------------------------------------------

	//	//Skill바꾸기
	//	//---------------------------------------------------------------------------
	//	OtherSlot->SlotSkill = SlotSkill;
	//	SlotSkill = OtherSkill;
	//	//---------------------------------------------------------------------------

	//	//Empty바꾸기
	//	//---------------------------------------------------------------------------
	//	bool OtherIsEmpty = OtherSlot->Empty;
	//	OtherSlot->Empty = Empty;
	//	Empty = OtherIsEmpty;
	//	//---------------------------------------------------------------------------
	//}
}
