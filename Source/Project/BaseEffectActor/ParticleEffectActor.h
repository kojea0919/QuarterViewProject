// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "ParticleEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AParticleEffectActor : public ABaseEffectActor
{
	GENERATED_BODY()

public:
	AParticleEffectActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	bool IsActive() { return Effect->IsActive(); }
	void SetActive(bool Active) { Effect->SetActive(Active); }
	void SetAutoActive(bool Active) { Effect->SetAutoActivate(Active); }

	void SetEffectEnable(bool Enable) { Effect->SetActive(Enable); }

public:
	//파티클이 끝나면 호출될 함수로 OnParticleSystemFinished를 등록
	UFUNCTION()
	virtual void OnParticleSystemFinished(UParticleSystemComponent* PSystem);

	//ParticleEffectActor를 상속받은 클래스마다 파티클이 끝나면 실행할 작업을 OnParticleSystemFinished_Impl에 구현
	virtual void OnParticleSystemFinished_Impl() PURE_VIRTUAL(ABaseEffectActor::OnParticleSystemFinished_Impl, );

protected:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;
	
};
