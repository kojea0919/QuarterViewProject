#include "Archer/Effect/UltimateArrowHit.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

AUltimateArrowHit::AUltimateArrowHit()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_ARROW(TEXT("/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_UltHit.P_Sparrow_UltHit"));
	if (PS_ARROW.Succeeded())
	{
		Effect->SetTemplate(PS_ARROW.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_HITSOUND(TEXT("/Game/GamePlay/Player/Archer/Sound/SC_UltimateHit.SC_UltimateHit"));
	if (SC_HITSOUND.Succeeded())
	{
		HitSound = SC_HITSOUND.Object;
	}
}

void AUltimateArrowHit::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnUltimateArrowHit(this);

}

void AUltimateArrowHit::SetEffectEnable(bool Enable)
{
	Super::SetEffectEnable(Enable);

	if (Enable && HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("Call"));
	}
}
