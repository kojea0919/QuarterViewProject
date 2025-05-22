#pragma once

#include "CoreMinimal.h"
#include "BaseEffectActor/ParticleEffectActor.h"
#include "UltimateArrowHit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AUltimateArrowHit : public AParticleEffectActor
{
	GENERATED_BODY()

public:
	AUltimateArrowHit();

	virtual void OnParticleSystemFinished_Impl();
	
	virtual void SetEffectEnable(bool Enable) override;
private:
	UPROPERTY()
	class USoundCue* HitSound;

};
