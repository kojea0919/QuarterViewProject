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

	//TargetLocation�������� ȸ���ϴ� �Լ�
	void RotateTargetLocation(FVector TargetVector);
	
	//�̵� ��ų ������ �� ���� �������� ������ Setting�ϴ� �Լ� (0~1)
	void SetMoveSkillEmissiveIntensity(float Intensity);

	void SetUseSkill(bool Enable) { IsUseSkill = Enable; }
	bool GetUseSkill() const { return IsUseSkill; }

	void SetLookMouseDirection(bool Enable) { LookMouseDirection = Enable; }

public:
	//�⺻ ����
	//----------------------------------------------------
	//�⺻ ���� �Է½� ȣ�� �Լ�
	void BasicAttackAction();

	//�⺻ ���� ��Ÿ�� ����� ������ ȣ��� �Լ�(���� �ʱ�ȭ �۾�)
	void BasicAttackMontageEnded();

	//�÷��̾��� �Է¿� ���� ���� �ִϸ��̼��� ����ϴ� �Լ�
	void BasicAttackComboCheck();

	//�⺻ ���� ����
	void BasicAttackShoot();
	//----------------------------------------------------

	//�̵� ��ų
	//----------------------------------------------------
	//�̵� ��ų �Է½� ȣ�� �Լ�
	void MoveSkillAction();

	//�̵� ��ų Foot Decal����
	void SpawnMoveSkillFootDecal();
	//----------------------------------------------------


private:
	//���콺 �������� ȸ���ϴ� �Լ�
	void RotateMouseDirection();

	void UpdateAttackTargetLocation();

	//MAterial�ʱ�ȭ �Լ�
	void InitMaterial();

	//���콺 �������� RotateSpeed��ŭ ȸ���ϴ� �Լ�
	void AddRotateMouseDirection(float DeltaTime);

private:
	//ī�޶� ���� ������Ʈ
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* QuarterViewCamera;
	//-----------------------------------------------------------------------------------------------

	//ĳ���� ���ݽ� ȸ��
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
	//SpringArm �⺻ ����
	float DefaultArmLength;

	//ĳ���� �̵� �ӵ�
	float DefaultSpeed = 600.0f;

	//�⺻ ���� ���� ����
	//-----------------------------------------
	//���� �⺻ ���� ������ ��Ÿ���� ����
	bool Attacking;

	//���� Combo
	int32 CurrentCombo;

	//�ִ� Combo
	int32 MaxCombo;

	//���� ����Ű �Է��� ���ȴ��� ��Ÿ���� ����
	bool ComboInput;

	//����Ű �Է��� �޴� ������ ��Ÿ���� ����
	//CanNextCombo�� true�� ���¿��� ����Ű�� ������ IsComboInput�� true�� �ٲ۴�
	bool CanNextCombo;

	//������ ���ȴ� ��ġ
	FVector AttackTargetLocation;
	//-----------------------------------------

	//���� ĳ���Ͱ� �̵��� �������� ��Ÿ���� ����
	bool MoveAble;

	//���� ĳ���Ͱ� �̵���ų�� �������� ��Ÿ���� ����
	bool MoveSkillOn;

	//���� �÷��̾ ��ų�� ����ߴ��� ��Ÿ���� ����
	bool IsUseSkill;

	//���콺 ������ �ٶ󺸰� ���� ��Ÿ���� ����
	bool LookMouseDirection;

	//ȸ�� �ӵ�
	float RotateSpeed;
};
