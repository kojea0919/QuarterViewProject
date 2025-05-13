#include "GamePlayEffect/JumpPointActor/JumpStartPoint.h"
#include "Components/SphereComponent.h"
#include "WorldSubSystem/JumpPointManagerSystem.h"
#include "GamePlayEffect/JumpPointActor/JumpEndPoint.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"

AJumpStartPoint::AJumpStartPoint()
	:IsCameraShake(false)
{
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));

	SetRootComponent(Collider);

	Collider->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void AJumpStartPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UJumpPointManagerSystem * Manager = GetWorld()->GetSubsystem<UJumpPointManagerSystem>();
	if (!Manager)
		return;

	const AJumpEndPoint * EndPoint = Manager->GetJumpEndPoint(TagName);
	if (nullptr == EndPoint)
		return;

	AArcher *Archer = Cast<AArcher>(OtherActor);
	if (nullptr == Archer || Archer->GetIsJumping())
		return;

	Archer->SetJumpEndPoint(EndPoint->GetActorLocation());
	Archer->SetIsCameraShakeJump(IsCameraShake);
	Archer->SetVisibleInteractionUI(true);
}

void AJumpStartPoint::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AArcher* Archer = Cast<AArcher>(OtherActor);
	if (nullptr == Archer)
		return;

	Archer->SetVisibleInteractionUI(false);
}

void AJumpStartPoint::BeginPlay()
{
	Super::BeginPlay();

	UJumpPointManagerSystem* Manager = GetWorld()->GetSubsystem<UJumpPointManagerSystem>();
	if (!Manager)
		return;
	Manager->AddJumpStartPoinArr(this);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &AJumpStartPoint::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AJumpStartPoint::EndOverlap);
}

void AJumpStartPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

