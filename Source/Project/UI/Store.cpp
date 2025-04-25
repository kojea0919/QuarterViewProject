// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "StoreSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragImage.h"
#include "StoreDragWidget.h"
#include "StoreWidgetDrag.h"

void UStore::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UStore::InitStore()
{
	for (size_t i = 0; i < StoreSlotNum; ++i)
	{
		UStoreSlot* StoreSlot = CreateWidget<UStoreSlot>(GetWorld(), StoreSlotClass);
		SlotArr.Push(StoreSlot);
		WrapBox->AddChild(StoreSlot);
	}
}

void UStore::NativeConstruct()
{
	Super::NativeConstruct();

	WrapBox = Cast<UWrapBox>(GetWidgetFromName(TEXT("WrapBox")));

	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("ExitStoreButton")));
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UStore::ClickExit);
	}
	
	DragDropBarButton = Cast<UButton>(GetWidgetFromName(TEXT("DragDropBar")));

	CanDrag = false;
}

FReply UStore::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 왼쪽 마우스 버튼이 눌렸을 때의 처리
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReplyResult.NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UStore::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UStoreDragWidget * DragWidget = CreateWidget<UStoreDragWidget>(GetOwningPlayer(), StoreDragWidgetClass);
	UStoreWidgetDrag* WidgetDrag = NewObject<UStoreWidgetDrag>(StoreWidgetDragClass);

	WidgetDrag->DefaultDragVisual = DragWidget;
	WidgetDrag->Pivot = EDragPivot::MouseDown;
	WidgetDrag->Offset = DragOffset;

	OutOperation = WidgetDrag;
}

bool UStore::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Call"));
	double MouseX, MouseY;
	GetOwningPlayer()->GetMousePosition(MouseX, MouseY);

	SetRenderTranslation(FVector2D(MouseX, MouseY));

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UStore::ClickExit()
{
	SetVisibility(ESlateVisibility::Hidden);
}

//void UStore::PressedDragDrop()
//{
//	IsPressedDragDropBar = true;
//	UE_LOG(LogTemp, Warning, TEXT("press"));
//}
//
//void UStore::ReleasedDragDrop()
//{
//	IsPressedDragDropBar = false;
//	UE_LOG(LogTemp, Warning, TEXT("release"));
//}
