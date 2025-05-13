// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpEndPoint.generated.h"

UCLASS()
class PROJECT_API AJumpEndPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AJumpEndPoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	const FString& GetTagName() const { return TagName; }

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TagName;
};
