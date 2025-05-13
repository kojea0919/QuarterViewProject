// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveCameraActor.generated.h"

UCLASS()
class PROJECT_API AMoveCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveCameraActor();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess = "true"))
	FRotator TargetCameraRotator;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector TargetCameraLocation;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float TargetCameraArmLength;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CameraTransformSpeed;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool IsUseRecorvery;//카메라를 Default로 바꾸는 경우에는 true
};
