// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Store.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
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
		UE_LOG(LogTemp, Warning, TEXT("Success"));
		ExitButton->OnClicked.AddDynamic(this, &UStore::ClickExit);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail"));
	}
	
}

void UStore::ClickExit()
{
	UE_LOG(LogTemp, Warning, TEXT("Call"));

	SetVisibility(ESlateVisibility::Hidden);
}
