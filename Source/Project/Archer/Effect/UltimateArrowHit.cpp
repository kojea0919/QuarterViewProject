#include "Archer/Effect/UltimateArrowHit.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Particles/ParticleSystem.h"

AUltimateArrowHit::AUltimateArrowHit()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_ARROW(TEXT("/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_UltHit.P_Sparrow_UltHit"));
	if (PS_ARROW.Succeeded())
	{
		Effect->SetTemplate(PS_ARROW.Object);
	}
}

void AUltimateArrowHit::OnParticleSystemFinished_Impl()
{
	EffectObjPool->ReturnUltimateArrowHit(this);
}
