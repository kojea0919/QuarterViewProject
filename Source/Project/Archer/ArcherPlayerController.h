// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project/UI/SlotKey.h"
#include "ArcherPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArcherPlayerController();

public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;
	
	//마우스의 월드 좌표 반환 함수
	FVector GetMouseWorldLocation();

	//Skill Quick Slot Key Setting
	void SetQuickSlotSkill(class UBaseSkill* Skill, ESkillQuickSlot SlotKey);

private:
	//마우스 입력시 마우스 포인터 방향으로 이동하는 함수
	//-------------------------------------------------
	void MoveTargetAction();
	void MoveTarget(FVector TargetLocation);
	//-------------------------------------------------

	void InitPlayerHUD();

private:
	//Player HUD
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class UPlayerHUD> PlayerHUDWidgetClass;

	class UPlayerHUD* PlayerHUD;
	//-------------------------------------------------
};
