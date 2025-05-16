// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircleFadeOutHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UCircleFadeOutHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void PlayCircleFadeOut();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	class UImage* FadeOutImage;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* DynMaterial;

	bool UpdateFade;

	float CurValue;
	const float Speed= 0.5;
};
