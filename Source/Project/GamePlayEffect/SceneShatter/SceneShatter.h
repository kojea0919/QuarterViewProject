// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "SceneShatter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ASceneShatter : public ASceneCapture2D
{
	GENERATED_BODY()
	
public:
	ASceneShatter();

public:
	void Shatter();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UGeometryCollectionComponent* GeometryCollectionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Plane;
};
