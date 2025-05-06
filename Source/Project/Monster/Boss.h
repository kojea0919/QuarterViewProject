
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
	void BasicComboAttack();
	void SpawnSawToothAttack();
	void SpawnSawTooth();

	void SpawnMeteorSkill();
	void ReadyToSpawnMeteor();
	void SpawnMeteor();

public:
	void SetRotateToPlayer(bool Enable) { RotateToPlayer = Enable; }

	int GetCurrentBasicCombo() const { return CurrentBasicComboAttackIdx; }
	void SetCurrentBasicCombo(int Combo) { CurrentBasicComboAttackIdx = Combo; }

	int GetBasicMaxCombo() const { return BasicComboAttackMaxIdx; }

	float GetDistanceToPlayer() const;
	bool CanBasicComboAttack() const;

protected:
	virtual void BeginPlay() override;

private:
	void BasicTypeDamageProc();

	FVector GetRandomVector();

	void LookPlayer(float DeltaTime);

private:
	//Particle
	//-----------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* BossLowerBodyEffect;		//하체 Particle

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* WeaponEffect;		//무기 Particle
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

	const float BasicComboAttackRange = 200.0f;

	const float SawToothAttackRange = 1200.0f;

	const float MeteorSpawnMinDist = 100.0f;
	const float MeteorSpawnMaxDist = 500.0f;
};
