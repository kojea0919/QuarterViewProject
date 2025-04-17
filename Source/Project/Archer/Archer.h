// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Archer.generated.h"

UCLASS()
class PROJECT_API AArcher : public ACharacter
{
	GENERATED_BODY()

public:
	AArcher();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* Controller) override;

public:
	bool GetMoveAble() const { return MoveAble; }
	void SetMoveAble(bool Enable);

	bool GetMoveSkillOn() const { return MoveSkillOn; }
	void SetMoveSkillOn(bool Enable) { MoveSkillOn = Enable; }

	void SetCanNextCombo(bool Enable) { CanNextCombo = Enable; }

	//TargetLocation방향으로 회전하는 함수
	void RotateTargetLocation(FVector TargetVector);
	
	//이동 스킬 눌렀을 때 몸을 빛나게할 강도를 Setting하는 함수 (0~1)
	void SetMoveSkillEmissiveIntensity(float Intensity);

	void SetUseSkill(bool Enable) { IsUseSkill = Enable; }
	bool GetUseSkill() const { return IsUseSkill; }

	void SetLookMouseDirection(bool Enable) { LookMouseDirection = Enable; }

public:
	//기본 공격
	//----------------------------------------------------
	//기본 공격 입력시 호출 함수
	void BasicAttackAction();

	//기본 공격 몽타주 재생이 끝나면 호출될 함수(변수 초기화 작업)
	void BasicAttackMontageEnded();

	//플레이어의 입력에 따라 다음 애니메이션을 재생하는 함수
	void BasicAttackComboCheck();

	//기본 공격 실행
	void BasicAttackShoot();
	//----------------------------------------------------

	//이동 스킬
	//----------------------------------------------------
	//이동 스킬 입력시 호출 함수
	void MoveSkillAction();

	//이동 스킬 Foot Decal생성
	void SpawnMoveSkillFootDecal();
	//----------------------------------------------------


private:
	//마우스 방향으로 회전하는 함수
	void RotateMouseDirection();

	void UpdateAttackTargetLocation();

	//MAterial초기화 함수
	void InitMaterial();

	//마우스 방향으로 RotateSpeed만큼 회전하는 함수
	void AddRotateMouseDirection(float DeltaTime);

private:
	//카메라 관련 컴포넌트
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* QuarterViewCamera;
	//-----------------------------------------------------------------------------------------------

	//캐릭터 공격시 회전
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(Visibleanywhere,BlueprintReadOnly, Category = CharacterMove, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* AttackRotationTimeline;

	UPROPERTY()
	UCurveFloat* RotationCurve;
	
	FOnTimelineFloat RotateTimelineProgress;
	FOnTimelineEvent RotateTimelineFinished;

	FRotator TargetRotator;
	FRotator StartRotator;



	UFUNCTION()
	void UpdateRotation(float Alpha);

	UFUNCTION()
	void TimelineFinishedFunction();
	//-----------------------------------------------------------------------------------------------


	class AArcherPlayerController* ArcherController;

	UPROPERTY()
	class UArcherAnimInstance* ArcherAnim;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class ABow* Bow;

	TArray<UMaterialInstanceDynamic*> DynMaterialArr;

	class AArcherMoveSkillFootDecal* LeftFootDecal;
	class AArcherMoveSkillFootDecal* RightFootDecal;

	class AMoveSkillFootDirt* FootDirtEffect;

private:
	//SpringArm 기본 길이
	float DefaultArmLength;

	//캐릭터 이동 속도
	float DefaultSpeed = 600.0f;

	//기본 공격 관련 변수
	//-----------------------------------------
	//현재 기본 공격 중인지 나타내는 변수
	bool Attacking;

	//현재 Combo
	int32 CurrentCombo;

	//최대 Combo
	int32 MaxCombo;

	//현재 공격키 입력이 눌렸는지 나타내는 변수
	bool ComboInput;

	//공격키 입력을 받는 시점을 나타내는 변수
	//CanNextCombo가 true인 상태에서 공격키가 눌러야 IsComboInput을 true로 바꾼다
	bool CanNextCombo;

	//공격이 눌렸던 위치
	FVector AttackTargetLocation;
	//-----------------------------------------

	//현재 캐릭터가 이동이 가능한지 나타내는 변수
	bool MoveAble;

	//현재 캐릭터가 이동스킬을 눌렀는지 나타내는 변수
	bool MoveSkillOn;

	//현재 플레이어가 스킬을 사용했는지 나타내는 변수
	bool IsUseSkill;

	//마우스 방향을 바라보게 할지 나타내는 변수
	bool LookMouseDirection;

	//회전 속도
	float RotateSpeed;
};
