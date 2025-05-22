#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "UltimateArrow.generated.h"

UCLASS()
class PROJECT_API AUltimateArrow : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	AUltimateArrow();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnParticleSystemFinished_Impl();

	void SetBoss(class ABoss* TargetBoss) { Boss = TargetBoss; }

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetOverlapStart();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollider;

	UPROPERTY()
	class ABoss* Boss;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* MoveForwardScaleCurve;

	float CurTime;
	float InitSpeed;
	float TargetOnSpeed;

	const float BaseDamage = 10000000;
};
