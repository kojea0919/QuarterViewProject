// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainLevelLight.generated.h"

UCLASS()
class PROJECT_API AMainLevelLight : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainLevelLight();

	void RecaptureSkyLight();
	void SetIntensityDirLight(float Intensity);

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite , meta = (AllowPrivateAccess = "true"))
	class USkyLightComponent* SkyLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UDirectionalLightComponent* DirLight;
};
