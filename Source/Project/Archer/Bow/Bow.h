// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bow.generated.h"

UCLASS()
class PROJECT_API ABow : public AActor
{
	GENERATED_BODY()
	
public:	
	ABow();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void BasicAttack();
	void SpecialAttack();

	void FlippingShot1();
	void FlippingShot2();
	void FlippingShot3();

private:
	void SpawnArrow(class ANiagaraEffectActor* ArrowEffect);
	void SpawnMuzzle(class ANiagaraEffectActor* MuzzleEffect);

	void SpawnArrowAddYawAngle(class ANiagaraEffectActor* ArrowEffect, float AddYawAngle);

private:
	UPROPERTY(VisibleAnywhere, Category = Pistol)
	USkeletalMeshComponent* Bow;
};
