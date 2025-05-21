
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Boss.generated.h"

UCLASS()
class PROJECT_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	ABoss();

public:
	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool LookPlayer(float DeltaTime);

	void BasicComboAttack();
	void SpawnSawToothAttack();
	void SpawnSawTooth();

	void SpawnMeteorSkill();
	void ReadyToSpawnMeteor();
	void SpawnMeteor();

	void DashSkill();
	void Dash();
	void DashEnd();
	void CreateDashEffect();

	void StoneSpike();
	void SpawnStoneSpikeMarkEffect();

	void DomainExpansion();
	void SpawnDomainExpansion();
	void RemoveDomainExpansion();

	void SoulSiphon();
	void SpawnSoulSiphonLoopEffect();
	void SoulSiphonEnd();
	void RemoveSoulSiphonLoopEffect();
	void PlaySoulSiphonEnd();
	void IllusionOff();

	void StartBehaviorTree();
	
	void BigSwing();
	void SpawnBigSwingMarkEffect();

	void ResetState();
	void PlayNextPhaseCinematic();
	void PlayDeadCinematic();

	void ClearDomainExpansionEffect() { DomainExpansionEffect = nullptr; }

	void DestroyDomainExpansion();
	void CleanSoulSiphonActor() { SoulSiphonActor = nullptr; }
	
	void SetStunState();

	void PlayStunLoop();

public:
	void CheckSoulSiphonOverlap();
	void CheckBigSwingOverlap();

public:
	void SetRotateToPlayer(bool Enable) { RotateToPlayer = Enable; }

	int GetCurrentBasicCombo() const { return CurrentBasicComboAttackIdx; }
	void SetCurrentBasicCombo(int Combo) { CurrentBasicComboAttackIdx = Combo; }

	int GetBasicMaxCombo() const { return BasicComboAttackMaxIdx; }

	float GetDistanceToPlayer() const;
	bool CanBasicComboAttack() const;

	void SetOutLineEnable(bool Enable);

	void MontageEnd();
	void SoulSiphonEndMontageEnd();

	bool GetPrevSkillIsDash() const { return PrevSkillIsDash; }

	FVector GetPlayerLocation() const;

	float GetBasicComboAttackRange() { return BasicComboAttackRange; }

	float GetCurrentHP() const { return CurHP; }
	float GetMaxHP() const { return MaxHP; }

	void PlayerDead();

	UFUNCTION(BlueprintCallable)
	void PlayShockWave();

	int GetCurrentPhase() const { return CurBossPhase; }

	void SetStartPhase2();
	void SetStartPhase3();



protected:
	virtual void BeginPlay() override;

private:
	void BasicTypeDamageProc(float Damage);

	FVector GetRandomVector();

	void IncreasePatternCount();
	void IncreaseSoulSiphonPatternCount();

	void UpdateShockWave(float DeltaTime);

private:
	//Particle
	//-----------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* BossLowerBodyEffect;		//하체 Particle

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* WeaponEffect;				//무기 Particle

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* DashSkillEffect;				//DashSkill Particle

	//-----------------------------------------------------------------------------

	//흑백 처리(영역 전개 스킬)용 TimeLine
	//-----------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DomainExpansion, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* DomainExpansionTimeline;

	UPROPERTY()
	UCurveFloat* ExpansionCurve;

	UPROPERTY()
	UCurveFloat* ExpansionCurveReverse;

	bool IsExpansion;

	FOnTimelineFloat DomainExpansionTimelineProgress;

	UFUNCTION()
	void UpdateDomainExpansionRadius(float Alpha);

	FTimerHandle RemoveDomainExpansionTimer;
	const float DomainExpansionHoldingTime = 10.f;

	class ABossDomainExpansionEffect* DomainExpansionEffect;
	//-----------------------------------------------------------------------------

	//흑백 처리 MPC
	//-----------------------------------------------------------------------------
	UMaterialParameterCollection* BlackAndWhiteMPC;
	
	UMaterialParameterCollectionInstance* BlackAndWhiteMPCInstance;
	//-----------------------------------------------------------------------------

	//충격파 PostProcess
	//-----------------------------------------------------------------------------
	UMaterialParameterCollection* ShockWaveMPC;

	UMaterialParameterCollectionInstance* ShockWaveMPCInstance;

	float CurTime;
	bool IsUpdateShockWave;
	//-----------------------------------------------------------------------------


	//Damage관련 변수
	//-----------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageText> DamageTextWidgetClass;

	const FVector DamageTextOffset = { 0.0f,-125.0f,60.0f };
	
	const float RandomVectorRange= 30;
	//-----------------------------------------------------------------------------

	class AArcher* Player;

	UPROPERTY()
	class UBossAnimInstance* BossAnim;

	bool RotateToPlayer;
	float RotateSpeed;

	int CurrentBasicComboAttackIdx;
	int BasicComboAttackMaxIdx;

	//스킬 사거리 관련 변수
	//------------------------------------------------
	const float BasicComboAttackRange = 400.0f;

	const float SawToothAttackRange = 1200.0f;

	const float MeteorSpawnMinDist = 100.0f;
	const float MeteorSpawnMaxDist = 900.0f;

	const float SoulSiphonForwardOffset = 200.0f;
	//const float SoulSiphonHeightOffset = 0.0f
	const float SoulSiphonCollisionRadius = 100.0f;
	const float BigSwingCollisionRadius = 350.f;
	//------------------------------------------------

	FTimerHandle DashEffectCreateTimer;	
	const float DashEffectTermTime = 0.15f;

	class ABossSoulSiphonLoopEffect* SoulSiphonLoopEffect;

	bool PrevSkillIsDash; 


	//체력 관련 변수
	//------------------------------------------------
	const float MaxHP = 1000000000.f;
	float CurHP = 1000000000.f;
	//------------------------------------------------
	
	//보스 페이즈 관련 변수
	//------------------------------------------------
	int CurBossPhase;
	const int MaxBosPhase = 3;

	const float Phase1ToPhase2HP = 900000000;
	const float Phase2ToPhase3HP = 100000000;

	bool NeedPlayLevelSequence;
	//------------------------------------------------

	//데미지 관련 변수
	//------------------------------------------------
	float BigSwingDamage = 150.0f;
	float SoulSiphonStartDamage = 50.0f;
	float SoulSiphonEndDamage = 150.0f;
	//------------------------------------------------

	//Pattern 잠시 휴식
	//------------------------------------------------
	const int MaxRestPatternCount = 1;
	int CurPatternCount;
	//------------------------------------------------

	//SoulSiphon
	//------------------------------------------------
	bool IsIllusionState;
	int SoulSiphonUsePatternCount;
	const int MaxSoulSiphonPatternCount = 3;	//일반 패턴을 10번 사용해야 SoulSiphon한번 사용 가능
	//------------------------------------------------


	FTimerHandle PlayNextCinematicTimer;

	class ASoulSiphonActor* SoulSiphonActor;
};
