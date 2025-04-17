// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"
#include "Project/Archer/Effect/ArcherBasicAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherBasicAttackMuzzleEffect.h"

ABow::ABow()
{
	PrimaryActorTick.bCanEverTick = true;

	Bow = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BOW"));

	RootComponent = Bow;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_BOW(TEXT("/Game/Player/Archer/Weapon/Bow2/Bow2.Bow2"));
	if (SM_BOW.Succeeded())
		Bow->SetSkeletalMesh(SM_BOW.Object);

	Bow->SetCollisionProfileName(TEXT("NoCollision"));
}

void ABow::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Good"));
	
}

void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%s"),*GetActorLocation().ToString());

}

void ABow::BasicAttack()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherBasicAttackArrowEffect* ArrowEffect = EffectObjPool->GetArcherBasicAttackArrowEffect();
	FTransform BowTransform = GetActorTransform();
	FTransform PlayerTransform = Owner->GetActorTransform();
	FTransform ArrowTransform = PlayerTransform;
	ArrowTransform.SetLocation(BowTransform.GetLocation());
	ArrowEffect->SpwanNiagaraEffect(ArrowTransform);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	FTransform MuzzleTransform = BowTransform;
	MuzzleTransform.SetLocation(BowTransform.GetLocation() + GetActorForwardVector() * 30.0f);

	MuzzleEffect->SpwanNiagaraEffect(MuzzleTransform);
}

