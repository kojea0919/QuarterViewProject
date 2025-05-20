#include "GamePlayEffect/LevelSequence/PlayeLevelSequenceActor.h"
#include "Components/BoxComponent.h"	
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Archer/ArcherPlayerController.h"
#include "Archer/Archer.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

APlayeLevelSequenceActor::APlayeLevelSequenceActor()
	: IsPlayed(false), IsUseCollision(true), ArcherController(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	SetRootComponent(BoxCollider);

	if(IsUseCollision)
		BoxCollider->SetCollisionProfileName(TEXT("OverlapAll"));
	else
		BoxCollider->SetCollisionProfileName(TEXT("NoCollision"));
}

void APlayeLevelSequenceActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayLevelSequence();
}

void APlayeLevelSequenceActor::PlayLevelSequence()
{
	if (IsPlayed)
		return;

	if (LevelSequence)
	{
		ALevelSequenceActor* SequenceActor;
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), SequenceActor);

		if (LevelSequencePlayer)
		{
			LevelSequencePlayer->OnFinished.AddDynamic(this, &APlayeLevelSequenceActor::FinishedSequence);

			LevelSequencePlayer->Play();
			IsPlayed = true;

			ArcherController = GetWorld()->GetFirstPlayerController<AArcherPlayerController>();
			if (ArcherController)
			{
				ArcherController->PlayLevelSequence(LevelSequencePlayer);

				AArcher* Archer = Cast<AArcher>(ArcherController->GetCharacter());
				if (Archer)
				{
					Archer->SetPlayingLevelSequenceState();
				}
			}
		}
	}
}

void APlayeLevelSequenceActor::BeginPlay()
{
	Super::BeginPlay();

	if(IsUseCollision)
		BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayeLevelSequenceActor::BeginOverlap);

	UBossBattleSubSystem * SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		switch (Type)
		{
		case ECinematicType::BossSpawn:
			SubSystem->SetBossSpawnSequence(this);
			break;
		case ECinematicType::BossPhase2:
			SubSystem->SetBossPhase2Sequence(this);
			break;
		case ECinematicType::BossPhase3:
			SubSystem->SetBossPhase3Sequence(this);
			break;
		case ECinematicType::BossDead:
			SubSystem->SetBossDeadSequence(this);
			break;
		}

	}



}

void APlayeLevelSequenceActor::FinishedSequence()
{
	if (ArcherController)
	{
		ArcherController->StopLevelSequence();

		AArcher* Archer = Cast<AArcher>(ArcherController->GetCharacter());
		if (Archer)
			Archer->SetNormalState();
	}
}
