// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarEclipse.generated.h"

UCLASS()
class PROJECT_API ASolarEclipse : public AActor
{
	GENERATED_BODY()
	
public:	
	ASolarEclipse();

	UFUNCTION(BlueprintCallable)
	void SolarEclipseStart();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Plane;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SolarEclipseProgressCurve;

	bool EclipseStart;
	float CurTime;
};
