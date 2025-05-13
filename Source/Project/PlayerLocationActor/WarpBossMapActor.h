#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarpBossMapActor.generated.h"

UCLASS()
class PROJECT_API AWarpBossMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWarpBossMapActor();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Collider;

	const float WarpOverlapTime = 1.0f;
	float CurOverlapTime;

};
