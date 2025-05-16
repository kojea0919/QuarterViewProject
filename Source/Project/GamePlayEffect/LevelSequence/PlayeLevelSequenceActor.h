// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayeLevelSequenceActor.generated.h"

UENUM(BlueprintType)
enum class ECinematicType : uint8
{
	BossSpawn UMETA(DisplayName = "BossSpawn"),
	BossPhase2 UMETA(DisplayName = "BossPhase2")
};

UCLASS()
class PROJECT_API APlayeLevelSequenceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayeLevelSequenceActor();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetIsPlayed() { IsPlayed = false; }

	void PlayLevelSequence();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void FinishedSequence();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool IsUseCollision;

	UPROPERTY(EditAnywhere, meta= (AllowPrivateAccess = "true"))
	ECinematicType Type;

	bool IsPlayed;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class ULevelSequence* LevelSequence;

	class ULevelSequencePlayer* LevelSequencePlayer;

	class AArcherPlayerController* ArcherController;
};
