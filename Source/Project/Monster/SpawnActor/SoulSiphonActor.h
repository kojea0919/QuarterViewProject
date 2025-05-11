// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulSiphonActor.generated.h"

UCLASS()
class PROJECT_API ASoulSiphonActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoulSiphonActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void SetBoss(class ABoss* Boss) { CurrentBoss = Boss; }

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* MeshCollision;

	class ABoss* CurrentBoss;
};
