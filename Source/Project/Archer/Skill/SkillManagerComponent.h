// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillManagerComponent.generated.h"

enum class EArcherSkillType : uint8
{
	Desperado = 0,
	Max
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_API USkillManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillManagerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void Init();

	class UBaseSkill* GetSkill(uint8 SkillType);

protected:
	UPROPERTY()
	TArray<class UBaseSkill*> SkillArr;
		
};
