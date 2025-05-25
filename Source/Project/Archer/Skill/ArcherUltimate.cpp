#include "Archer/Skill/ArcherUltimate.h"
#include "Archer/Archer.h"
#include "Archer/Animation/ArcherAnimInstance.h"

UArcherUltimate::UArcherUltimate()
{
	SetCoolTime(60.0f);
}

bool UArcherUltimate::Use()
{
	if (!Super::Use())
		return false;

	if (Archer)
		Archer->PlayUltimateSequence();

	return true;
}

void UArcherUltimate::End()
{
	Super::End();

	if (Archer)
		Archer->UltimateEnd();
}
