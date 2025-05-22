// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Boss.h"
#include "Engine/DamageEvents.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "WorldSubSystem/BossBattleSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"
#include "UI/DamageText.h"
#include "DamageType/ArcherDamageType.h"
#include "Monster/Animation/BossAnimInstance.h"
#include "Monster/Effect/BasicHitEffect.h"
#include "Monster/Effect/BossSawToothSkillEffect.h"
#include "Monster/Effect/BossSpawnMeteorReadyEffect.h"
#include "Monster/Effect/BossMeteorTargetAreaMarkEffect.h"
#include "Monster/Effect/BossBigSwingAreaMarkEffect.h"
#include "Monster/BossAIController.h"
#include "Monster/Effect/BossStoneSpikeAreaMarkEffect.h"
#include "Monster/Effect/BossDomainExpansionEffect.h"
#include "Monster/Effect/BossSoulSiphonLoopEffect.h"
#include "Monster/SpawnActor/SoulSiphonActor.h"
#include "DamageType/BossStiffDamageType.h"
#include "DamageType/BossKnockBackDamageType.h"
#include "DamageType/BossCameraShakeDamageType.h"

ABoss::ABoss()
	: CurTime(0),IsUpdateShockWave(false), Player(nullptr), BossAnim(nullptr), RotateToPlayer(false), RotateSpeed(650.f), CurrentBasicComboAttackIdx(0),
	BasicComboAttackMaxIdx(3), SoulSiphonLoopEffect(nullptr), PrevSkillIsDash(false), CurBossPhase(1), NeedPlayLevelSequence(false), CurPatternCount(0),
	IsIllusionState(false), SoulSiphonUsePatternCount(0), SoulSiphonActor(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Create
	//---------------------------------------------
	BossLowerBodyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LOWERBODYEFFECT"));
	WeaponEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("WEAPONEFFECT"));
	DashSkillEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DASHSKILLEFFECT"));

	DomainExpansionTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DOMAINEXPANSIONTIMELINE"));
	//---------------------------------------------

	//Components Init
	//---------------------------------------------
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BOSS(TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog"));
	if (SK_BOSS.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BOSS.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_LOWERBODYEFFECT(TEXT("/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_ShadowTrailsCharSelect.P_ShadowTrailsCharSelect"));
	if (PS_LOWERBODYEFFECT.Succeeded())
	{
		BossLowerBodyEffect->SetTemplate(PS_LOWERBODYEFFECT.Object);
	}
	BossLowerBodyEffect->SetupAttachment(GetMesh());
	BossLowerBodyEffect->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_WEAPONEFFECT(TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Effects/P_Sevarog_Homescreen_Hammer.P_Sevarog_Homescreen_Hammer"));
	if (PS_WEAPONEFFECT.Succeeded())
	{
		WeaponEffect->SetTemplate(PS_WEAPONEFFECT.Object);
	}
	WeaponEffect->SetupAttachment(GetMesh(), TEXT("FX_Trail_R_01"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_DASHSKILLEFFECT(TEXT("/Game/Luos8Elements/Particles/Dark/Par_4E_Dark_Atk_01.Par_4E_Dark_Atk_01"));
	if (PS_DASHSKILLEFFECT.Succeeded())
	{
		DashSkillEffect->SetTemplate(PS_DASHSKILLEFFECT.Object);
	}
	DashSkillEffect->SetupAttachment(GetCapsuleComponent());
	DashSkillEffect->SetWorldScale3D(FVector(3.0f));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	//---------------------------------------------

	//Curve Setting
	//---------------------------------------------
	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_RADIUSCURVE(TEXT("/Game/GamePlay/GamePlayEffect/BlackAndWhite/C_BlackAndWhiteRadius.C_BlackAndWhiteRadius"));

	if (C_RADIUSCURVE.Succeeded())
	{  
		ExpansionCurve = C_RADIUSCURVE.Object;
	}

	const ConstructorHelpers::FObjectFinder<UCurveFloat> C_RADIUSCURVEREVERSE(TEXT("/Game/GamePlay/GamePlayEffect/BlackAndWhite/C_BlackAndWhiteRadiusReverse.C_BlackAndWhiteRadiusReverse"));

	if (C_RADIUSCURVEREVERSE.Succeeded())
	{
		ExpansionCurveReverse = C_RADIUSCURVEREVERSE.Object;
	}
	//---------------------------------------------

	//MPC Setting
	BlackAndWhiteMPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Game/GamePlay/GamePlayEffect/BlackAndWhite/MPC_BlackAndWhite.MPC_BlackAndWhite"));
	ShockWaveMPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Game/GamePlay/GamePlayEffect/Shockwave/MPC_ShockWave.MPC_ShockWave"));

	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//---------------------------------------------
}

void ABoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UBossAnimInstance* Anim = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (Anim)
		BossAnim = Anim;

}

float ABoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UArcherDamageType* DamageType = nullptr;
	if (DamageEvent.DamageTypeClass)
	{
		DamageType = DamageEvent.DamageTypeClass->GetDefaultObject<UArcherDamageType>();
	}
	
	if (nullptr == DamageType)
		return 0;

	switch (DamageType->GetDamageType())
	{
	case EArcherDamageType::Basic:
		BasicTypeDamageProc((int)Damage);
		break;
	}

	if(!IsIllusionState)
		CurHP -= (int)Damage;

	AArcherPlayerController* ArcherController = Player->GetController<AArcherPlayerController>();
	if (ArcherController)
	{
		ArcherController->SetBossCurrentHP(CurHP);
	}

	if (CurHP <= Phase1ToPhase2HP && CurBossPhase == 1)
	{
		CurBossPhase = 2;
		NeedPlayLevelSequence = true;
	}
	else if (CurHP <= Phase2ToPhase3HP && CurBossPhase == 2)
	{
		CurBossPhase = 3;
		NeedPlayLevelSequence = true;
	}
	else if (CurHP <= 0 && CurBossPhase == 3)
	{
		PlayDeadCinematic();

		ArcherController->SetVisibleBossClearWindow();
		ArcherController->RemoveMouseReverse();

		SetActorLocation(FVector(0.0f));
	}


	return 0.0f;
}

float ABoss::GetDistanceToPlayer() const
{
	float Distance = 0.0f;
	if (Player)
	{
		Distance = (Player->GetActorLocation() - GetActorLocation()).Length();
	}

	return Distance;
}

bool ABoss::CanBasicComboAttack() const
{
	if (GetDistanceToPlayer() < BasicComboAttackRange)
		return true;
	
	return false;
}

void ABoss::SetOutLineEnable(bool Enable)
{
	GetMesh()->SetRenderCustomDepth(Enable);
}

void ABoss::MontageEnd()
{
	//현재 몽타주가 끝나면 BlackBoard 갱신
	//-------------------------------------------------------------------
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->MontageEnd();
	}
	else
		return;
	//-------------------------------------------------------------------
	
	IncreasePatternCount();					//휴식을 위한 PatternCount 증가
	IncreaseSoulSiphonPatternCount();		//SoulSiphonPattern을 위한 Count 증가


	//LevelSequence 재생이 필요한 경우 1초 대기 후 Cinematic재생 함수 호출
	//-------------------------------------------------------------------
	if (NeedPlayLevelSequence)
	{
		UWorld* World = GetWorld();

		if (nullptr != World)
			World->GetTimerManager().SetTimer(PlayNextCinematicTimer, this, &ABoss::PlayNextPhaseCinematic, 1.0f, false);
		
		AIController->StopBehaviorTree();
	}
	//-------------------------------------------------------------------
}

void ABoss::SoulSiphonEndMontageEnd()
{
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->SoulSiphonSkillEnd();
	}

	if (NeedPlayLevelSequence)
	{
		UWorld* World = GetWorld();

		if (nullptr != World)
			World->GetTimerManager().SetTimer(PlayNextCinematicTimer, this, &ABoss::PlayNextPhaseCinematic, 1.2f, false);

		AIController->StopBehaviorTree();
	}
}

FVector ABoss::GetPlayerLocation() const
{
	if (Player)
		return Player->GetActorLocation();
	return FVector();
}

void ABoss::PlayerDead()
{
	//플레이어가 죽었으면 ai멈추기
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->StopBehaviorTree();
	}
}

void ABoss::PlayShockWave()
{
	IsUpdateShockWave = true;
	CurTime = 0.f;

	if (ShockWaveMPCInstance)
	{
		ShockWaveMPCInstance->SetScalarParameterValue(TEXT("Enable"), IsUpdateShockWave);
	}
}

void ABoss::PlayNextPhaseCinematic()
{
	NeedPlayLevelSequence = false; 

	if (CurBossPhase == 2)
	{
		UBossBattleSubSystem * SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
		if (SubSystem)
		{
			SubSystem->PlayBossPhase2Sequence();
		}

		if (Player)
			Player->SetPlayingLevelSequenceState();
	}
	else if (CurBossPhase == 3)
	{
		UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
		if (SubSystem)
		{
			SubSystem->PlayBossPhase3Sequence();
		}

		if (Player)
			Player->SetPlayingLevelSequenceState();
	}
}

void ABoss::PlayDeadCinematic()
{
	NeedPlayLevelSequence = false;

	if (BossAnim)
		BossAnim->StopCurMontage();

	//플레이어가 죽었으면 ai멈추기
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->StopBehaviorTree();
	}

	UBossBattleSubSystem* SubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (SubSystem)
	{
		SubSystem->PlayBossDeadSequence();
	}
}

void ABoss::SetStartPhase2()
{
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->SetStartPhase2(true);
	}
}

void ABoss::SetStartPhase3()
{
	DestroyDomainExpansion();

	//새로운 패턴
	//------------------------------

	//------------------------------
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
	//Player Setting
	//------------------------------
	AArcher* TargetPlayer = Cast<AArcher>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (TargetPlayer)
	{
		Player = TargetPlayer;

		AArcherPlayerController* ArcherController = Player->GetController<AArcherPlayerController>();
		if (ArcherController)
			ArcherController->SetBoss(this);
	}
	//------------------------------

	DashSkillEffect->Deactivate();

	//Timeline Setting
	//------------------------------
	DomainExpansionTimelineProgress.BindUFunction(this, FName("UpdateDomainExpansionRadius"));
	DomainExpansionTimeline->AddInterpFloat(ExpansionCurve, DomainExpansionTimelineProgress);
	//------------------------------
		
	//MPC Instance Setting
	//------------------------------
	UWorld* World = GetWorld();
	if (!World) return;

	BlackAndWhiteMPCInstance = World->GetParameterCollectionInstance(BlackAndWhiteMPC);
	ShockWaveMPCInstance = World->GetParameterCollectionInstance(ShockWaveMPC);
	//------------------------------
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (RotateToPlayer)
	{
		LookPlayer(DeltaTime);
	}

	if (IsUpdateShockWave) 
	{
		UpdateShockWave(DeltaTime);
	}
}

void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss::BasicComboAttack()
{
	if (BossAnim)
	{
		BossAnim->PlayBasicComboAttackMontage();

		CurrentBasicComboAttackIdx = 0;
	}
}

void ABoss::SpawnSawToothAttack()
{
	if (BossAnim)
	{
		BossAnim->PlaySpawnSawToothMontage();
	}
}

void ABoss::SpawnSawTooth()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	if (nullptr == Player)
		return;

	//플레이어와 특정 거리 이내에 톱니 생성
	//------------------------------------------------------------------------
	FVector PlayerLocation = Player->GetActorLocation();
	FVector2D RandomDir = FMath::RandPointInCircle(1.0f);
	RandomDir.Normalize();

	FVector SawSpawnLocation = PlayerLocation + FVector(RandomDir.X, RandomDir.Y, 0.0f) * SawToothAttackRange;
	//------------------------------------------------------------------------

	ABossSawToothSkillEffect * SawToothEffect = EffectObjectPool->GetBossSawToothSkillEffect();
	FVector SawToPlayerVector = PlayerLocation - SawSpawnLocation;
	SawToPlayerVector.Z = 0;
	FRotator SawToPlayerRotator = SawToPlayerVector.GetSafeNormal().Rotation();


	SawToothEffect->SetActorLocation(SawSpawnLocation + FVector(0.0f,0.0f,30.0f));
	SawToothEffect->SetActorRotation(SawToPlayerRotator);
	SawToothEffect->StartTelegraphRectangle();

}

void ABoss::SpawnMeteorSkill()
{
	if (BossAnim)
	{
		BossAnim->PlaySpawnMeteorMontage();
	}
}

void ABoss::ReadyToSpawnMeteor()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	ABossSpawnMeteorReadyEffect* Effect = EffectObjectPool->GetBossSpawnMeteorReadyEffect();
	FTransform BossTransform = GetActorTransform();
	BossTransform.AddToTranslation(FVector(0.0f, 0.0f, -84.f));
	Effect->SpwanNiagaraEffect(BossTransform);
}

void ABoss::SpawnMeteor()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;


	ABossMeteorTargetAreaMarkEffect* Effect = EffectObjectPool->GetBossMeteorTargetAreaMarkEffect();

	//보스와 특정 거리 이내에 메테오 생성
	//------------------------------------------------------------------------
	FVector BossLocation = GetActorLocation();
	FVector2D RandomDir = FMath::RandPointInCircle(1.0f);
	RandomDir.Normalize();

	float Range = FMath::RandRange(MeteorSpawnMinDist, MeteorSpawnMaxDist);

	FVector MeteorTargetLocation = BossLocation + FVector(RandomDir.X, RandomDir.Y, 0.0f) * Range + FVector(0.0f,0.0f,-84.f);
	//------------------------------------------------------------------------

	FTransform BossTransform = GetActorTransform();
	BossTransform.SetLocation(MeteorTargetLocation);
	Effect->SpwanNiagaraEffect(BossTransform);

}

void ABoss::DashSkill()
{
	if (BossAnim)
	{
		BossAnim->PlayDashSkillStartMontae();
		RotateToPlayer = true;
	}
}

void ABoss::Dash()
{
	UWorld* World = GetWorld();

	if (nullptr != World)
		World->GetTimerManager().SetTimer(DashEffectCreateTimer, this, &ABoss::CreateDashEffect, DashEffectTermTime, false);
	
	GetCharacterMovement()->MaxWalkSpeed = 3500.0f;
	PrevSkillIsDash = true;

	ABossAIController * AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->MoveToLocation(Player->GetActorLocation(),50.f);
	}
}

void ABoss::DashEnd()
{
	PrevSkillIsDash = false;
	DashSkillEffect->Deactivate();
	GetMesh()->SetVisibility(true);
	BossLowerBodyEffect->Activate();
	WeaponEffect->Activate();

	GetCharacterMovement()->MaxWalkSpeed = 600.0f;


	if (Player)
	{
		FVector BossToPlayer = Player->GetActorLocation() - GetActorLocation();
		BossToPlayer.Normalize();
		SetActorRotation(BossToPlayer.Rotation());
	}

	//후속타 진행
	if (BossAnim)
		BossAnim->PlayBigSwingMontage();
}

void ABoss::CreateDashEffect()
{
	DashSkillEffect->Activate();
	GetMesh()->SetVisibility(false);
	BossLowerBodyEffect->Deactivate();
	WeaponEffect->Deactivate();
}

void ABoss::StoneSpike()
{
	if (BossAnim)
	{
		BossAnim->PlayStoneSpikeMontage();
	}
}

void ABoss::SpawnStoneSpikeMarkEffect()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	ABossStoneSpikeAreaMarkEffect* Effect = EffectObjectPool->GetBossStoneSpikeAreaMarkEffect();
	FTransform BossTransform = GetActorTransform();
	BossTransform.SetLocation(GetMesh()->GetSocketLocation(TEXT("StoneSpikeMarkPos")));

	Effect->SpwanNiagaraEffect(BossTransform);
	Effect->SetOwner(this);

}

void ABoss::DomainExpansion()
{
	if (BossAnim)
	{
		BossAnim->PlayDomainExpansion();

		ABossAIController* AIController = Cast<ABossAIController>(Controller);
		if (AIController)
		{
			AIController->SetStartPhase2(false);
		}
	}
}

void ABoss::SpawnDomainExpansion()
{
	if (BlackAndWhiteMPCInstance)
	{
		FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("HammerCenter"));

		BlackAndWhiteMPCInstance->SetVectorParameterValue(TEXT("SpawnActorLocation"), SpawnLocation);
	}

	DomainExpansionTimeline->PlayFromStart();

	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	DomainExpansionEffect = EffectObjectPool->GetBossDomainExpansionEffect();
	DomainExpansionEffect->SpwanNiagaraEffect(GetMesh()->GetSocketTransform(TEXT("HammerCenter")));
	DomainExpansionEffect->SetOwner(this);

	if (Player)
		Player->SetSlowState(true);

	UWorld* World = GetWorld();
	if (nullptr != World)
		World->GetTimerManager().SetTimer(RemoveDomainExpansionTimer, this, &ABoss::RemoveDomainExpansion, DomainExpansionHoldingTime, false);

}

void ABoss::RemoveDomainExpansion()
{
	if (BlackAndWhiteMPCInstance)
	{
		FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("HammerCenter"));

		BlackAndWhiteMPCInstance->SetVectorParameterValue(TEXT("SpawnActorLocation"), SpawnLocation);
	}

	DomainExpansionTimeline->Reverse();

	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	DomainExpansionEffect = EffectObjectPool->GetBossDomainExpansionEffect();
	DomainExpansionEffect->SetReverse();
	DomainExpansionEffect->SpwanNiagaraEffect(GetMesh()->GetSocketTransform(TEXT("HammerCenter")));
	DomainExpansionEffect->SetOwner(this);
}

void ABoss::SoulSiphon()
{
	if (BossAnim)
	{
		BossAnim->PlaySoulSiphon();
	}
}

void ABoss::SpawnSoulSiphonLoopEffect()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	if (SoulSiphonLoopEffect == nullptr)
	{
		SoulSiphonLoopEffect = EffectObjectPool->GetBossSoulSiphonLoopEffect();

		SoulSiphonLoopEffect->SetActorTransform(Player->GetSoulSiphonEffectPos());
	}
}

void ABoss::SoulSiphonEnd()
{
	IsIllusionState = false;

	//플레이어에게 넉백 공격
	UGameplayStatics::ApplyDamage(
		Player,
		SoulSiphonEndDamage,
		GetInstigatorController(),
		this,
		UBossCameraShakeDamageType::StaticClass());

	SoulSiphonUsePatternCount = 0;
}

void ABoss::RemoveSoulSiphonLoopEffect()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	if (SoulSiphonLoopEffect)
	{
		EffectObjectPool->ReturnBossSoulSiphonLoopEffect(SoulSiphonLoopEffect);
		SoulSiphonLoopEffect = nullptr;
	}
}

void ABoss::PlaySoulSiphonEnd()
{
	if (BossAnim)
		BossAnim->PlaySoulSiphonEnd();
}

void ABoss::IllusionOff()
{
	if (BossAnim)
		BossAnim->Montage_Stop(0);

	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->SetIllusionEnd(true);
		AIController->MontageEnd();
		AIController->StopMovement();
	}
}

void ABoss::StartBehaviorTree()
{
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->StartBehaviorTree();
	}
}

void ABoss::BigSwing()
{
	if (BossAnim)
	{
		BossAnim->PlayBigSwingMontage();
	}
}

void ABoss::SpawnBigSwingMarkEffect()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	ABossBigSwingAreaMarkEffect* Effect = EffectObjectPool->GetBossBigSwingAreaMarkEffect();
	FTransform BossTransform = GetActorTransform();
	BossTransform.AddToTranslation(FVector(0.0f, 0.0f, -84.f));

	Effect->SpwanNiagaraEffect(BossTransform);
}

void ABoss::ResetState()
{
	DestroyDomainExpansion();

	GetWorld()->GetTimerManager().ClearTimer(PlayNextCinematicTimer);

	RotateToPlayer = false;
	CurrentBasicComboAttackIdx = 0;
	PrevSkillIsDash = false;

	CurBossPhase = 1;
	CurPatternCount = 0;
	IsIllusionState = false;
	SoulSiphonUsePatternCount = 0;

	if (SoulSiphonActor)
		SoulSiphonActor->Destroy();
}

void ABoss::DestroyDomainExpansion()
{
	//흑백처리 제거
	if (BlackAndWhiteMPCInstance)
	{
		GetWorld()->GetTimerManager().ClearTimer(RemoveDomainExpansionTimer);
		DomainExpansionTimeline->Stop();
		BlackAndWhiteMPCInstance->SetScalarParameterValue(TEXT("Radius"), 0);
	}

	if (DomainExpansionEffect)
		DomainExpansionEffect->OnNiagaraSystemFinished_Impl();
}

void ABoss::SetStunState()
{
	//플레이어가 죽었으면 ai멈추기
	ABossAIController* AIController = Cast<ABossAIController>(Controller);
	if (AIController)
	{
		AIController->StopBehaviorTree();

		if (BossAnim)
			BossAnim->PlayStunLoop();
	}
}

void ABoss::CheckSoulSiphonOverlap()
{
	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel4);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector SphereLocation = GetActorLocation() + GetActorForwardVector() * SoulSiphonForwardOffset;

	bool IsHit = GetWorld()->SweepMultiByObjectType(HitResults,
		SphereLocation, SphereLocation,
		GetActorQuat(), ObjectQueryParams,
		FCollisionShape::MakeSphere(SoulSiphonCollisionRadius),
		Params);

	/*DrawDebugSphere(GetWorld(),
		SphereLocation,
		SoulSiphonCollisionRadius, 12,
		FColor::Green, false, 2);*/

	//충돌이 된 경우
	//------------------------------------------------------------
	if (IsHit)
	{
		//데미지 처리
		//----------------------------------------------
		for (auto& Hit : HitResults)
		{
			UGameplayStatics::ApplyDamage(
				Hit.GetActor(),
				SoulSiphonStartDamage,
				GetInstigatorController(),
				this,
				UBossStiffDamageType::StaticClass());
		}
		//----------------------------------------------


		//BlackBoard Update
		//----------------------------------------------
		ABossAIController* AIController = Cast<ABossAIController>(Controller);
		if (AIController)
		{
			AIController->SetUsingSoulSiphonState(true);		//현재 상태를 SoulSiphon을 사용한 상태로 만들기
			AIController->SetCanUseSoulSiphon(false);			//SoulSiphon을 사용했으므로 CanUseSoulSiphon을 false로 만들기
		}
		//----------------------------------------------

		SoulSiphonActor = GetWorld()->SpawnActor<ASoulSiphonActor>(SphereLocation, FRotator());
		SoulSiphonActor->SetBoss(this);

		//맞은 시점의 플레이어, 보스 Transform 저장
		//----------------------------------------------
		UBossBattleSubSystem * BossBattle = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
		BossBattle->SaveBossTransform(GetActorTransform());
		BossBattle->SavePlayerTransform(Player->GetActorTransform());
		//----------------------------------------------

		IsIllusionState = true;	//IsIllusionState를 true로 해서 데미지를 안 받게 설정
	}
	//------------------------------------------------------------
}

void ABoss::CheckBigSwingOverlap()
{
	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel4);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector SphereLocation = GetActorLocation();

	bool IsHit = GetWorld()->SweepMultiByObjectType(HitResults,
		SphereLocation, SphereLocation,
		GetActorQuat(), ObjectQueryParams,
		FCollisionShape::MakeSphere(BigSwingCollisionRadius),
		Params);

	//DrawDebugSphere(GetWorld(),
	//	SphereLocation,
	//	BigSwingCollisionRadius, 12,
	//	FColor::Green, false, 2);

	//충돌이 된 경우
	if (IsHit)
	{
		for (auto& Hit : HitResults)
		{
			//BigSwing은 반원 Check로직 추가
			FVector BossToHitActorVector = (Hit.GetActor()->GetActorLocation() - GetActorLocation());
			BossToHitActorVector.Normalize();
			float DotResult = BossToHitActorVector.Dot(GetActorForwardVector());
			if (DotResult < 0)
				continue;

			UGameplayStatics::ApplyDamage(
				Hit.GetActor(),
				BigSwingDamage,
				GetInstigatorController(),
				this,
				UBossKnockBackDamageType::StaticClass());
		}
	}
}

void ABoss::BasicTypeDamageProc(float Damage)
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	ABasicHitEffect* HitEffect = EffectObjectPool->GetBasicHitEffect();

	FTransform TargetTransform = GetActorTransform();
	TargetTransform.SetScale3D(FVector(3.0f));

	HitEffect->SpwanNiagaraEffect(TargetTransform);

	UDamageText * DamageText = CreateWidget<UDamageText>(GetWorld(), DamageTextWidgetClass);
	if (DamageText)
	{
		DamageText->AddToViewport();
		DamageText->SetDamageText(Damage);

		//데미지 Text위치 지정
		//------------------------------------
		FVector2D ScreenPos;
		FVector UILocation = GetActorLocation() + DamageTextOffset + GetRandomVector();

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (nullptr == PlayerController)
			return;

		UGameplayStatics::ProjectWorldToScreen(PlayerController, UILocation, ScreenPos);
		DamageText->SetPlayerController(PlayerController);
		DamageText->SetOwnerLocation(UILocation);

		DamageText->SetPositionInViewport(ScreenPos);
		DamageText->PlayBasicDamageTextAnimation();
		//------------------------------------
	}

}

FVector ABoss::GetRandomVector()
{
	FVector ReturnVector; 
	float Range = RandomVectorRange;
	ReturnVector.X = FMath::RandRange(-Range, Range);
	ReturnVector.Y = FMath::RandRange(-Range, Range);
	ReturnVector.Z = FMath::RandRange(-Range, Range);
	return ReturnVector;
}

void ABoss::IncreasePatternCount()
{
	++CurPatternCount;

	if (CurPatternCount == MaxRestPatternCount)
	{
		ABossAIController* AIController = Cast<ABossAIController>(Controller);
		if (AIController)
		{
			AIController->SetRestPattern();
			CurPatternCount = 0;
		}
	}

}

void ABoss::IncreaseSoulSiphonPatternCount()
{
	if (SoulSiphonUsePatternCount > MaxSoulSiphonPatternCount)
		return;

	++SoulSiphonUsePatternCount;

	if (SoulSiphonUsePatternCount == MaxSoulSiphonPatternCount)
	{
		ABossAIController* AIController = Cast<ABossAIController>(Controller);
		if (AIController)
		{
			AIController->SetCanUseSoulSiphon(true);
		}
	}
}

void ABoss::UpdateShockWave(float DeltaTime)
{
	CurTime += DeltaTime;
	if (CurTime >= 1.0f)
	{
		IsUpdateShockWave = false;
		
		ShockWaveMPCInstance->SetScalarParameterValue(TEXT("Enable"), IsUpdateShockWave);
	}

	if (ShockWaveMPCInstance)
	{
		ShockWaveMPCInstance->SetScalarParameterValue(TEXT("Progress"), CurTime);
	}
}

bool ABoss::LookPlayer(float DeltaTime)
{
	if (nullptr == Player)
		return false;

	//플레이어가 오른쪽에 있는지 왼쪽에 있는지 판별
	//-----------------------------------------
	FVector BossForward = GetActorForwardVector();
	FVector BossToPlayerVector = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	if (BossForward.Equals(BossToPlayerVector, 0.07f))
	{
		RotateToPlayer = false;
		return true;
	}

	FVector Cross = FVector::CrossProduct(BossForward, BossToPlayerVector);

	float RotationDir = Cross.Z > 0 ? 1.0f : -1.0f;
	
	AddActorWorldRotation(FRotator(0.0f, DeltaTime * RotationDir * RotateSpeed, 0.0f));
	//-----------------------------------------

	return false;
}

void ABoss::UpdateDomainExpansionRadius(float Alpha)
{
	if (BlackAndWhiteMPCInstance)
	{
		BlackAndWhiteMPCInstance->SetScalarParameterValue(TEXT("Radius"), Alpha);
	}
}

