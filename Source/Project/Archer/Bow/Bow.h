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

private:
	UPROPERTY(VisibleAnywhere, Category = Pistol)
	USkeletalMeshComponent* Bow;
};
