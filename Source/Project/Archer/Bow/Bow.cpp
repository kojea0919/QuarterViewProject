// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"
#include "Project/Archer/Effect/ArcherBasicAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherSpecialAttackArrowEffect.h"
#include "Project/Archer/Effect/ArcherBasicAttackMuzzleEffect.h"
#include "Project/BaseEffectActor/NiagaraEffectActor.h"
#include "Project/Archer/Effect/ArcherBigArrowEffect.h"

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
}

void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABow::BasicAttack()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherBasicAttackArrowEffect* ArrowEffect = EffectObjPool->GetArcherBasicAttackArrowEffect();
	SpawnArrow(ArrowEffect);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	SpawnMuzzle(MuzzleEffect);
}

void ABow::SpecialAttack()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherSpecialAttackArrowEffect* ArrowEffect = EffectObjPool->GetArcherSpecialAttackArrowEffect();
	SpawnArrow(ArrowEffect);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	SpawnMuzzle(MuzzleEffect);
}

void ABow::FlippingShot1()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherBigArrowEffect* ArrowEffect = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrow(ArrowEffect);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	SpawnMuzzle(MuzzleEffect);
}

void ABow::FlippingShot2()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherBigArrowEffect* ArrowEffect1 = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrowAddYawAngle(ArrowEffect1, -3);
	AArcherBigArrowEffect* ArrowEffect2 = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrowAddYawAngle(ArrowEffect2, 3);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	SpawnMuzzle(MuzzleEffect);
}

void ABow::FlippingShot3()
{
	UEffectObjectPool* EffectObjPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjPool)
		return;

	//Effect가 플레이어의 앞 방향으로 발사
	//-----------------------------------------------------------
	AArcherBigArrowEffect* ArrowEffect1 = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrowAddYawAngle(ArrowEffect1, -3);
	AArcherBigArrowEffect* ArrowEffect2 = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrowAddYawAngle(ArrowEffect2, 0);
	AArcherBigArrowEffect* ArrowEffect3 = EffectObjPool->GetArcherBigArrowEffect();
	SpawnArrowAddYawAngle(ArrowEffect3, 3);
	//-----------------------------------------------------------

	AArcherBasicAttackMuzzleEffect* MuzzleEffect = EffectObjPool->GetArcherBasicAttackMuzzleEffect();
	SpawnMuzzle(MuzzleEffect);
}

void ABow::SpawnArrow(ANiagaraEffectActor* ArrowEffect)
{
	SpawnArrowAddYawAngle(ArrowEffect, 0);
}

void ABow::SpawnMuzzle(ANiagaraEffectActor* MuzzleEffect)
{
	FTransform BowTransform = GetActorTransform();
	FTransform MuzzleTransform = BowTransform;
	MuzzleTransform.SetLocation(BowTransform.GetLocation() + GetActorForwardVector() * 30.0f);

	MuzzleEffect->SpwanNiagaraEffect(MuzzleTransform);
}

void ABow::SpawnArrowAddYawAngle(ANiagaraEffectActor* ArrowEffect, float AddYawAngle)
{
	//Rotation은 플레이어의 Rotation을 사용하고 위치는 현재 Bow의 위치를 사용
	//--------------------------------------------------------------------
	FTransform BowTransform = GetActorTransform();
	FTransform PlayerTransform = Owner->GetActorTransform();
	FTransform ArrowTransform = PlayerTransform;
	ArrowTransform.SetRotation(ArrowTransform.Rotator().Add(0, AddYawAngle, 0).Quaternion());

	ArrowTransform.SetLocation(BowTransform.GetLocation());
	//--------------------------------------------------------------------

	ArrowEffect->SpwanNiagaraEffect(ArrowTransform);
}

