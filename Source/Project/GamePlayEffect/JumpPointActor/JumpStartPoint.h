#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpStartPoint.generated.h"

UCLASS()
class PROJECT_API AJumpStartPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AJumpStartPoint();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	const FString& GetTagName() const { return TagName; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString TagName;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool IsCameraShake;

};
