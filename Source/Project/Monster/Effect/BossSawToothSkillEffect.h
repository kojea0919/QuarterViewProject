// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "BossSawToothSkillEffect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ABossSawToothSkillEffect : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	ABossSawToothSkillEffect();

public:
	UFUNCTION()
	virtual void OnTelegraphFinished(UNiagaraComponent* PSystem);

	virtual void OnParticleSystemFinished_Impl() override;

	void StartTelegraphRectangle();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void UpdateScale(float DeltaTime);
	void UpdateLocation(float DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraSystem* TelegraphRectangleEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraComponent* TelegraphComp;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	//톱니 이동 거리
	const float SawToothMoveDistance = 2500.f;

	//장판 Width
	const float TelegraphRectangleWidth = 70.0f;

	//장판 LifeTime
	const float TelegraphRectangleLifeTime = 2.0f;

	//톱니 Scale 크기 변환 속도
	const float SawToothScaleSpeed = 0.5f;

	//현재 Scale이 Update가 필요한지 나타내는 변수
	bool NeedToUpdateScale;

	//톱니를 이동 시킬지 나타내는 변수
	bool IsCanMove;

	//현재 이동 거리
	float CurMoveDistance;

	//이동 속도
	float MoveSpeed;

	const float SawToothDamage = 100.0f;
};
