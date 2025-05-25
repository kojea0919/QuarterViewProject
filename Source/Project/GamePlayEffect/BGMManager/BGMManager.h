#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BGMManager.generated.h"

UCLASS()
class PROJECT_API ABGMManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABGMManager();

public:
	void StopBGM() const;

	void PlayPhase1BGM() const;

	UFUNCTION(BlueprintCallable)
	void PlayPhase2BGM() const;

	void PlayPhase3BGM() const;

	bool IsPlayingBGM() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = " true"))
	class UAudioComponent* BGMPlayer;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"))
	class USoundCue* BossPhase1BGM;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"))
	class USoundCue* BossPhase2BGM;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"))
	class USoundCue* BossPhase3BGM;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"))
	class USoundCue* BaseBGM;
};
