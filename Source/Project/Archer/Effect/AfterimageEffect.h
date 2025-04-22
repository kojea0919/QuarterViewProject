// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project/BaseEffectActor/MeshEffectActor.h"
#include "AfterimageEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AAfterimageEffect : public AMeshEffectActor
{
	GENERATED_BODY()
	
public:
	AAfterimageEffect();

	void CopyAnimationPos(USkeletalMeshComponent* MasterComponent);

	void SetOpacity(float NewOpacity);

protected:
	virtual void Tick(float DeltaTime) override;

private:
	void LoadMaterial() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPoseableMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* DynMaterial;

	float Opacity;
	float OpacitySpeed;
};
