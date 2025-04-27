// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreDragWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UStoreDragWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetWidgetReference(UUserWidget* Reference) { WidgetReference = Reference; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;
	
};
