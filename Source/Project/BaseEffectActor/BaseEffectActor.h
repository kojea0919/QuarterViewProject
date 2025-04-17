// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

UCLASS()
class PROJECT_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEffectActor();

public:
	//Tick�� ����ϴ� EffectActor�� Ȱ��ȭ
	void SetTickEnable(bool Enable) { SetActorTickEnabled(Enable); }

	virtual void SetEffectEnable(bool Enable) {};

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = EffectObjectPool)
	class UEffectObjectPool* EffectObjPool;
};
