#include "GamePlayEffect/Light/MainLevelLight.h"
#include "Components/SkyLightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

AMainLevelLight::AMainLevelLight()
{
	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SKY"));
	DirLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("DIRECTIONAL"));

	SkyLight->SetupAttachment(RootComponent);
	DirLight->SetupAttachment(RootComponent);
}

void AMainLevelLight::RecaptureSkyLight()
{
	if (SkyLight)
		SkyLight->RecaptureSky();
}

void AMainLevelLight::SetIntensityDirLight(float Intensity)
{
	if (DirLight)
		DirLight->SetIntensity(Intensity);
}

void AMainLevelLight::BeginPlay()
{
	Super::BeginPlay();

	UBossBattleSubSystem * BossBattleSubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (BossBattleSubSystem)
		BossBattleSubSystem->SetMainLevelLight(this);
}

