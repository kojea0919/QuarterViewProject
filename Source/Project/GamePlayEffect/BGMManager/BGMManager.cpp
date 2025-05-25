#include "GamePlayEffect/BGMManager/BGMManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Archer/ArcherPlayerController.h"

ABGMManager::ABGMManager()
{
	PrimaryActorTick.bCanEverTick = false;

	BGMPlayer = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUNDPLAYER"));

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_PHASE1BGM(TEXT("/Game/GamePlay/Sound/SC_Phaer1BGM.SC_Phaer1BGM"));
	if (SC_PHASE1BGM.Succeeded())
		BossPhase1BGM = SC_PHASE1BGM.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_PHASE2BGM(TEXT("/Game/GamePlay/Sound/SC_Phase2BGM.SC_Phase2BGM"));
	if (SC_PHASE2BGM.Succeeded())
		BossPhase2BGM = SC_PHASE2BGM.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_PHASE3BGM(TEXT("/Game/GamePlay/Sound/SC_Phase3BGM.SC_Phase3BGM"));
	if (SC_PHASE3BGM.Succeeded())
		BossPhase3BGM = SC_PHASE3BGM.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SC_BASEBGM(TEXT("/Game/GamePlay/Sound/SC_BaseBGM.SC_BaseBGM"));
	if (SC_BASEBGM.Succeeded())
		BaseBGM = SC_BASEBGM.Object;
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

		BGMPlayer->SetSound(BaseBGM);
		BGMPlayer->Play();
	}

}

void ABGMManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

