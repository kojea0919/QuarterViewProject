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
	//파티클이 끝나면 호출될 함수로 OnNiagaraSystemFinished를 등록
	UFUNCTION()
	virtual void OnNiagaraSystemFinished(UNiagaraComponent* PSystem);

	//NiagaraEffectActor를 상속받은 클래스마다 파티클이 끝나면 실행할 작업을 OnParticleSystemFinished_Impl에 구현
	virtual void OnNiagaraSystemFinished_Impl() PURE_VIRTUAL(ABaseEffectActor::OnNiagaraSystemFinished_Impl, );


protected:
	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraSystem* NiagaraEffect;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	class UNiagaraComponent* NiagaraComp;
	
};
