// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillQuickSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragImage.h"
#include "SkillImageDragDropOperation.h"
#include "SkillBase/BaseSkill.h"

void USkillQuickSlot::SetMaterial(UMaterialInstanceDynamic* Material)
{
	SkillImage->SetBrushFromMaterial(Material);
}

void USkillQuickSlot::SetSkill(UBaseSkill* Skill)
{
	if (Skill)
	{
		SlotSkill = Skill;

		SetMaterial(SlotSkill->GetUIMaterial());
		Empty = false;

		SetSkillTypeImage(Skill);
	}
}

void USkillQuickSlot::SetSlotKeyText(const TCHAR* SlotKey)
{
	if (SlotKeyText)
		SlotKeyText->SetText(FText::FromString(SlotKey));
}

void USkillQuickSlot::SetRemainCoolTimeVisible(bool Enable)
{
	if (RemainCoolTime)
	{
		if (Enable)
		{
			RemainCoolTime->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			RemainCoolTime->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void USkillQuickSlot::UpdateRemainCoolTime()
{
	if (RemainCoolTime)
	{
		//스킬로 부터 남은 쿨타임 계산
		float CoolTime = SlotSkill->GetRemainCoolTime();

		//정수 부분과 소수 부분 분리
		uint8 IntegerPart = CoolTime;
		uint8 DecimalPart = (CoolTime - IntegerPart) * 10;

		FString RemainTimeString = FString::Printf(TEXT("%d.%d"), IntegerPart, DecimalPart);

		RemainCoolTime->SetText(FText::FromString(RemainTimeString));
	}
}

void USkillQuickSlot::PlaySkillCoolTimeEndAnimation()
{
	if (SkillCoolTimeEndAnimation)
	{

		PlayAnimation(SkillCoolTimeEndAnimation);
	}
}

void USkillQuickSlot::PlayUseSkillAnimation()
{
	if(UseSkillAnimation)
		PlayAnimation(UseSkillAnimation);
}

void USkillQuickSlot::PlayFailUseSkillAnimation()
{
	if (FailUseSkillAnimation)
		PlayAnimation(FailUseSkillAnimation);
}

void USkillQuickSlot::UseSkill()
{
	if (nullptr == SlotSkill)
		return;

	if (!SlotSkill->IsCoolDownActive())
	{
		SlotSkill->Use();
	}
	/*else
	{
		PlayFailUseSkillAnimation();
	}*/
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

	//SkillCoolTimeEnd = Cast<UImage>(GetWidgetFromName(FName("Img_SkillCoolTimeEnd")));
	SlotImage = Cast<UImage>(GetWidgetFromName(FName("Img_SlotImage")));
	SkillImage = Cast<UImage>(GetWidgetFromName(FName("Img_SkillImage")));
	SlotKeyText = Cast<UTextBlock>(GetWidgetFromName(FName("Text_SlotKey")));
	
	SkillTypeImage = Cast<UImage>(GetWidgetFromName(FName("Img_SkillType")));
	if (SkillTypeImage)
		SkillTypeImage->SetVisibility(ESlateVisibility::Hidden);

	RemainCoolTime = Cast<UTextBlock>(GetWidgetFromName(FName("Text_RemainCoolTime")));

	ChargingSkillTypeTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Player/UI/Skill/Texture/T_ChargingSkillTexture.T_ChargingSkillTexture"));
	ComboSkillTypeTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Player/UI/Skill/Texture/T_ComboSkillTexture.T_ComboSkillTexture"));

}

void USkillQuickSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	SlotImage->SetColorAndOpacity(FLinearColor(1.0f,1.0f,0.0f,0.5f));
}

void USkillQuickSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
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
	UMaterialInstanceDynamic* SkillMaterial = Cast<UMaterialInstanceDynamic>(SkillImage->GetBrush().GetResourceObject());
	DragImage->SetMaterial(SkillMaterial);
	//-------------------------------------------------------------------------------

	USkillImageDragDropOperation* DragDrop = NewObject<USkillImageDragDropOperation>(DragImage);
	OutOperation = DragDrop;
	DragDrop->DefaultDragVisual = DragImage;
	DragDrop->Pivot = EDragPivot::CenterCenter;
	DragDrop->SetDragObject(this);
}

bool USkillQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillImageDragDropOperation* DragDropOperation = Cast<USkillImageDragDropOperation>(InOperation);
	if (nullptr == DragDropOperation)
		return false;
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
	if (IsValid(OtherSlot))
	{
		//Material 바꾸기
		//---------------------------------------------------------------------------
		UMaterialInstanceDynamic* ThisMaterial = Cast<UMaterialInstanceDynamic>(SkillImage->GetBrush().GetResourceObject());
		UMaterialInstanceDynamic* OtherMaterial = Cast<UMaterialInstanceDynamic>(OtherSlot->SkillImage->GetBrush().GetResourceObject());

		OtherSlot->SetMaterial(ThisMaterial);
		SetMaterial(OtherMaterial);
		//---------------------------------------------------------------------------

		//SkillSlot바꾸기
		//---------------------------------------------------------------------------
		UBaseSkill* OtherSkill = OtherSlot->SlotSkill;
		if (OtherSkill)
			OtherSkill->SetQuickSlot(this);
		if (SlotSkill)
			SlotSkill->SetQuickSlot(OtherSlot);
		//---------------------------------------------------------------------------

		//Skill바꾸기
		//---------------------------------------------------------------------------
		OtherSlot->SlotSkill = SlotSkill;
		SlotSkill = OtherSkill;

		SetSkillTypeImage(SlotSkill);
		OtherSlot->SetSkillTypeImage(OtherSlot->SlotSkill);
		//---------------------------------------------------------------------------

		//Empty바꾸기
		//---------------------------------------------------------------------------
		bool OtherIsEmpty = OtherSlot->Empty;
		OtherSlot->Empty = Empty;
		Empty = OtherIsEmpty;
		//---------------------------------------------------------------------------
	}
}

void USkillQuickSlot::SetSkillTypeImage(const UBaseSkill* Skill)
{
	if (nullptr == SkillTypeImage)
		return;

	//SkillType 표시
	//---------------------------------------------------------------------------
	UTexture2D* TargetTexture = nullptr;

	switch (Skill->GetSkillType())
	{
	case ESkillType::Base:
		SkillTypeImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	case ESkillType::Charging:
		TargetTexture = ChargingSkillTypeTexture;
		break;
	case ESkillType::Combo:
		TargetTexture = ComboSkillTypeTexture;
		break;
	default:
		SkillTypeImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (TargetTexture)
	{
		SkillTypeImage->SetBrushFromTexture(TargetTexture);
		SkillTypeImage->SetVisibility(ESlateVisibility::Visible);
	}
	//---------------------------------------------------------------------------
}
