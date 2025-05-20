// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/SpawnActor/SoulSiphonActor.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Archer/Archer.h"
#include "Monster/Boss.h"
#include "WorldSubSystem/BossBattleSubSystem.h"

ASoulSiphonActor::ASoulSiphonActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	MeshCollision = CreateDefaultSubobject<USphereComponent>(TEXT("COLLISION"));

	RootComponent = Mesh;
	MeshCollision->SetupAttachment(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Ball_01.SM_Ball_01"));
	if (MESH.Succeeded())
		Mesh->SetStaticMesh(MESH.Object);

	MeshCollision->SetSphereRadius(60);
	MeshCollision->SetCollisionProfileName(TEXT("Enemy"));
}

void ASoulSiphonActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoulSiphonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASoulSiphonActor::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	AArcher* Archer = Cast<AArcher>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Archer)
	{
		Archer->CreateSceneShatter();
	}

	UBossBattleSubSystem * BossBattleSubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (BossBattleSubSystem)
	{
		FTransform BossTransform = BossBattleSubSystem->GetSaveBossTransform();
		FTransform PlayerTransform = BossBattleSubSystem->GetSavePlayerTransform();

		//플레이어를 보스 방향으로 회전
		//----------------------------------------------------------
		FVector PlayerToBossVector = BossTransform.GetLocation() - PlayerTransform.GetLocation();
		PlayerToBossVector.Normalize();	
		PlayerTransform.SetRotation(PlayerToBossVector.Rotation().Quaternion());
		//----------------------------------------------------------

		Archer->SetActorTransform(PlayerTransform);
		CurrentBoss->SetActorTransform(BossTransform);

		CurrentBoss->SpawnSoulSiphonLoopEffect();
		Archer->SetBoundState();

		CurrentBoss->IllusionOff();

		CurrentBoss->CleanSoulSiphonActor();
	}



	Destroy();

	return 0.0f;
}

