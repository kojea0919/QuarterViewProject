// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "StoreSlot.h"

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
	if (DragDropBarButton)
	{
		DragDropBarButton->OnPressed.AddDynamic(this, &UStore::ClickDragDrop);
	}
}

void UStore::ClickExit()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UStore::ClickDragDrop()
{
	FVector2D MousePos;
	GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePos.X, MousePos.Y);

	UCanvasPanelSlot * CanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot);
	if (CanvasPanelSlot)
	{
		CanvasPanelSlot->SetPosition(MousePos);
	}
}
