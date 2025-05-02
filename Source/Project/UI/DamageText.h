// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageText.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UDamageText : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDamageText(float Damage);

	void SetOwnerLocation(const FVector& Location) { OwnerLocation = Location; }

	void SetPlayerController(APlayerController* Controller) { PlayerController = Controller; }

	void PlayBasicDamageTextAnimation();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY()
	class UTextBlock* DamageText;
	
	FVector OwnerLocation; //이 Text를 생성한 Owner의 위치

	APlayerController* PlayerController;

	//ScaleDown Animation
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* BasicDamageTextAnimation;
};
