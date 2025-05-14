#include "GamePlayEffect/LevelSequence/PlayeLevelSequenceActor.h"
#include "Components/BoxComponent.h"	
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Archer/ArcherPlayerController.h"
#include "Archer/Archer.h"

APlayeLevelSequenceActor::APlayeLevelSequenceActor()
	: IsPlayed(false), ArcherController(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	SetRootComponent(BoxCollider);

	BoxCollider->SetCollisionProfileName(TEXT("OverlapAll"));
}

void APlayeLevelSequenceActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			AArcher* Archer = Cast<AArcher>(OtherActor);
			if (Archer)
			{
				ArcherController = Archer->GetController<AArcherPlayerController>();
				if (ArcherController)
				{
					ArcherController->PlayLevelSequence(LevelSequencePlayer);
				}
			}
		}
	}
}

void APlayeLevelSequenceActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayeLevelSequenceActor::BeginOverlap);


}

void APlayeLevelSequenceActor::FinishedSequence()
{
	if (ArcherController)
	{
		ArcherController->StopLevelSequence();
	}
}
