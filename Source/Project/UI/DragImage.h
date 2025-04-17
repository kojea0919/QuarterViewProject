// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragImage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UDragImage : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMaterial(UMaterialInstanceDynamic* Material);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	class UImage* DragImage;

	UMaterialInstanceDynamic* DragImageMaterial = nullptr;
	
};
