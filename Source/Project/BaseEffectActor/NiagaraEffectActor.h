// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor.h"
#include "NiagaraEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ANiagaraEffectActor : public ABaseEffectActor
{
	GENERATED_BODY()

public:
	virtual void SpwanNiagaraEffect(const FTransform& Transform);

	virtual void SpawnAndAttachNiagaraEffect(class USkeletalMeshComponent* TargetMesh, FName SocketName);

	virtual void SetEffectEnable(bool Enable);
public:
	//��ƼŬ�� ������ ȣ��� �Լ��� OnNiagaraSystemFinished�� ���
	UFUNCTION()
	virtual void OnNiagaraSystemFinished(UNiagaraComponent* PSystem);

	//NiagaraEffectActor�� ��ӹ��� Ŭ�������� ��ƼŬ�� ������ ������ �۾��� OnParticleSystemFinished_Impl�� ����
	virtual void OnNiagaraSystemFinished_Impl() PURE_VIRTUAL(ABaseEffectActor::OnNiagaraSystemFinished_Impl, );


protected:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraSystem* NiagaraEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraComponent* NiagaraComp;
	
};
