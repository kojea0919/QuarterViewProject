
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

	void SoulSiphon();
	void SpawnSoulSiphonLoopEffect();
	void SoulSiphonEnd();
	void RemoveSoulSiphonLoopEffect();
	void PlaySoulSiphonEnd();
	void IllusionOff();

	void StartBehaviorTree();
	
	void BigSwing();
	void SpawnBigSwingMarkEffect();
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

protected:
	virtual void BeginPlay() override;

private:
	void BasicTypeDamageProc();

	FVector GetRandomVector();

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

	FOnTimelineFloat DomainExpansionTimelineProgress;

	UFUNCTION()
	void UpdateDomainExpansionRadius(float Alpha);
	//-----------------------------------------------------------------------------

	//흑백 처리 MPC
	//-----------------------------------------------------------------------------
	UMaterialParameterCollection* BlackAndWhiteMPC;
	
	UMaterialParameterCollectionInstance* BlackAndWhiteMPCInstance;
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
	const float BasicComboAttackRange = 300.0f;

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
	const float MaxHP = 300000000.f;
	float CurHP = 300000000.f;
	//------------------------------------------------

};
