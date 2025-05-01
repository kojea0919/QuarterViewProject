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

	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void BasicAttack();
	void SpecialAttack();

	void FlippingShot1();
	void FlippingShot2();
	void FlippingShot3();

	void ArrowShowerShot();

	void PulseShot();

	void SetChargingEffect(bool Enable);

private:
	//화살 Effect를 생성하는 함수
	//--------------------------------------------------------------------------------------------------
	void SpawnArrow(class ANiagaraEffectActor* ArrowEffect, bool UsePlayerDir = true);

	//AddYawAngle만큼 화살 회전
	//플레이어의 앞방향으로 쏘려면 UsePlayerDir을 true로
	//활의 앞방향으로 쏘려면 false로
	void SpawnArrowAddYawAngle(class ANiagaraEffectActor* ArrowEffect, float AddYawAngle, bool UsePlayerDir = true);
	//--------------------------------------------------------------------------------------------------
	void SpawnMuzzle(class ANiagaraEffectActor* MuzzleEffect);


private:
	UPROPERTY(VisibleAnywhere, Category = Pistol)
	USkeletalMeshComponent* Bow;

	UPROPERTY(VisibleAnywhere, Category = Material)
	UMaterialInstanceDynamic* DynMaterial;
};
