#include "GamePlayEffect/BGMManager/BGMManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Archer/ArcherPlayerController.h"

ABGMManager::ABGMManager()
{
	PrimaryActorTick.bCanEverTick = false;

	BGMPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDPLAYER"));

	static ConstructorHelpers::FObjectFinder<USoundCue> SW_PHASE1BGM(TEXT("/Game/GamePlay/Sound/SC_Phaer1BGM.SC_Phaer1BGM"));
	if (SW_PHASE1BGM.Succeeded())
		BossPhase1BGM = SW_PHASE1BGM.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SW_PHASE2BGM(TEXT("/Game/GamePlay/Sound/SC_Phase2BGM.SC_Phase2BGM"));
	if (SW_PHASE2BGM.Succeeded())
		BossPhase2BGM = SW_PHASE2BGM.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SW_PHASE3BGM(TEXT("/Game/GamePlay/Sound/SC_Phase3BGM.SC_Phase3BGM"));
	if (SW_PHASE3BGM.Succeeded())
		BossPhase3BGM = SW_PHASE3BGM.Object;
}

void ABGMManager::StopBGM() const
{
	if (BGMPlayer->IsPlaying())
		BGMPlayer->Stop();
}

void ABGMManager::PlayPhase1BGM() const
{
	if (BossPhase1BGM)
	{
		if (BGMPlayer->IsPlaying())
			BGMPlayer->Stop();

		BGMPlayer->SetSound(BossPhase1BGM);
		BGMPlayer->Play();
	}
}

void ABGMManager::PlayPhase2BGM() const
{
	if (BossPhase2BGM)
	{
		if (BGMPlayer->IsPlaying())
			BGMPlayer->Stop();

		BGMPlayer->SetSound(BossPhase2BGM);
		BGMPlayer->Play();
	}
}

void ABGMManager::PlayPhase3BGM() const
{
	if (BossPhase3BGM)
	{
		if (BGMPlayer->IsPlaying())
			BGMPlayer->Stop();

		BGMPlayer->SetSound(BossPhase3BGM);
		BGMPlayer->Play();
	}
}

bool ABGMManager::IsPlayingBGM() const
{
	if (!BGMPlayer)
		return false;

	return BGMPlayer->IsPlaying();
}

void ABGMManager::BeginPlay()
{
	Super::BeginPlay();

	AArcherPlayerController * ArcherController = GetWorld()->GetFirstPlayerController<AArcherPlayerController>();
	if (ArcherController)
	{
		ArcherController->SetBGMManager(this);
	}

}

void ABGMManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

