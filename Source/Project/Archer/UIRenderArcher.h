// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UIRenderArcher.generated.h"

UCLASS()
class PROJECT_API AUIRenderArcher : public ACharacter
{
	GENERATED_BODY()

public:
	AUIRenderArcher();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	//SceneCapture
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneCapture, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* SceneCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneCapture, meta = (AllowPrivateAccess = "true"))
	class UTextureRenderTarget2D* RenderTarget;
	//-----------------------------------------------------------------------------------------------
};
