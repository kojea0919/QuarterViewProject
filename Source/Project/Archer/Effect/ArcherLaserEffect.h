// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/MeshEffectActor.h"
#include "ArcherLaserEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherLaserEffect : public AMeshEffectActor
{
	GENERATED_BODY()

public:
	AArcherLaserEffect();

	virtual void Tick(float DeltaTime) override;

private:
	void UpdateScale(float DeltaTime);

private:
	virtual void LoadMaterial() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Cylinder;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* DynMaterial;

	UPROPERTY(VisibleAnywhere, Category = LaserBeam)
	UParticleSystemComponent* LaserBeam;

	float InitLength;		//길이

	//크기
	//-----------------------------
	float InitScale;		//초기 크기	
	float CurScale;			//현재 크기
	//-----------------------------

	float ScaleDecreaseSpeed;	//스케일 감소 속도

};
