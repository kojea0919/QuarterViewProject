#include "Archer/Effect/UltimateArrow.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Monster/Boss.h"
#include "UltimateArrowHit.h"
#include "Kismet/GameplayStatics.h"
#include "DamageType/ArcherBasicDamageType.h"

AUltimateArrow::AUltimateArrow()
	: CurTime(0.0f), InitSpeed(500.0f), TargetOnSpeed(1300.0f)
{
	//PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_ARROW(TEXT("/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Arrow_Ultimate.P_Arrow_Ultimate"));
	if (PS_ARROW.Succeeded())
	{
		Effect->SetTemplate(PS_ARROW.Object);
	}

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(BoxCollider);
	Effect->SetupAttachment(BoxCollider);

	BoxCollider->SetCollisionProfileName(TEXT("Player"));
	BoxCollider->SetGenerateOverlapEvents(false);
	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_MOVESCALE(TEXT("/Game/GamePlay/Player/Archer/CF_UltimateArrowForwardScale.CF_UltimateArrowForwardScale"));

	if (C_MOVESCALE.Succeeded())
	{
		MoveForwardScaleCurve = C_MOVESCALE.Object;
	}

}

void AUltimateArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Boss)
	{
		CurTime += DeltaTime;
		float Alpha = MoveForwardScaleCurve->GetFloatValue(CurTime);

		FVector ArrowToBoss = (Boss->GetActorLocation()+ FVector(0.0f,0.0f,90.0f)) - GetActorLocation();
		ArrowToBoss.Normalize();
		FVector CurMoveDir = FMath::Lerp(ArrowToBoss, GetActorForwardVector(), Alpha);
		CurMoveDir.Normalize();
	
		float Speed;
		if (Alpha >= 0.9)
			Speed = InitSpeed;
		else
			Speed = TargetOnSpeed;

		AddActorWorldOffset(CurMoveDir *DeltaTime * Speed);
		SetActorRotation(CurMoveDir.ToOrientationQuat());
	}

}

void AUltimateArrow::OnParticleSystemFinished_Impl()
{
	BoxCollider->SetGenerateOverlapEvents(false);
	EffectObjPool->ReturnUltimateArrow(this);
	CurTime = 0;
}

void AUltimateArrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	BoxCollider->SetGenerateOverlapEvents(false);
	EffectObjPool->ReturnUltimateArrow(this);
	CurTime = 0;


	AUltimateArrowHit * HitEffect = EffectObjPool->GetUltimateArrowHit();
	HitEffect->SetActorLocation(GetActorLocation());

	UGameplayStatics::ApplyDamage(
		OtherActor,
		BaseDamage + FMath::RandRange(-1000000,100000),
		GetInstigatorController(),
		this,
		UArcherBasicDamageType::StaticClass());
}

void AUltimateArrow::SetOverlapStart()
{
	BoxCollider->SetGenerateOverlapEvents(true);
}

void AUltimateArrow::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AUltimateArrow::OnComponentBeginOverlap);
}
