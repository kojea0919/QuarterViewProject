// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	
	//���콺�� ���� ��ǥ ��ȯ �Լ�
	FVector GetMouseWorldLocation();

private:
	//���콺 �Է½� ���콺 ������ �������� �̵��ϴ� �Լ�
	//-------------------------------------------------
	void MoveTargetAction();
	void MoveTarget(FVector TargetLocation);
	//-------------------------------------------------

};
