// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "StoreWidgetDrag.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStoreWidgetDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetWidgetReference(UUserWidget* Reference) { WidgetReference = Reference; }
	void SetDragOffset(FVector2D Pos) { DragOffset = Pos; }

	UUserWidget* GetReference() { return WidgetReference; }
	FVector2D GetDragOffset() const { return DragOffset; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;
};
