// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayeLevelSequenceActor.generated.h"

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

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void FinishedSequence();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	bool IsPlayed;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class ULevelSequence* LevelSequence;

	class ULevelSequencePlayer* LevelSequencePlayer;

	class AArcherPlayerController* ArcherController;
};
