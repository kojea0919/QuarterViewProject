#include "PlayerLocationActor/WarpBossMapActor.h"
#include "Components/SphereComponent.h"
#include "WorldSubSystem/BossBattleSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AWarpBossMapActor::AWarpBossMapActor()
	: CurOverlapTime(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("COLLIDER"));

	RootComponent = Collider;

	Collider->SetCollisionProfileName(TEXT("OverlapAll"));


}

void AWarpBossMapActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetActorTickEnabled(true);

	CurOverlapTime = 0.0f;

}

void AWarpBossMapActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetActorTickEnabled(false);
}

void AWarpBossMapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurOverlapTime += DeltaTime;

	if (CurOverlapTime >= WarpOverlapTime)
	{
		UBossBattleSubSystem * SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
		if (SubSystem)
		{
			const FTransform & PlayerInitTransform = SubSystem->GetPlayerSpawnTransform();

			ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			Player->SetActorTransform(PlayerInitTransform);
		}
	}
}

void AWarpBossMapActor::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AWarpBossMapActor::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AWarpBossMapActor::EndOverlap);
}


