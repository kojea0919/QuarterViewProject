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
	//��ƼŬ�� ������ ȣ��� �Լ��� OnParticleSystemFinished�� ���
	UFUNCTION()
	virtual void OnParticleSystemFinished(UParticleSystemComponent* PSystem);

	//ParticleEffectActor�� ��ӹ��� Ŭ�������� ��ƼŬ�� ������ ������ �۾��� OnParticleSystemFinished_Impl�� ����
	virtual void OnParticleSystemFinished_Impl() PURE_VIRTUAL(ABaseEffectActor::OnParticleSystemFinished_Impl, );

protected:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;
	
};
