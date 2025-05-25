// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Item/ItemStruct.h"
#include "Archer.generated.h"


enum class EPlayerState
{
	Normal,
	Bound,
	Stiff,
	Down,
	PlayingLevelSequence,
	UsingUltimate
};

class UCurveVector;

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

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

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

	void SetBowChargingEffect(bool Enable);

	void RangeMarkOn(float Range);
	void RangeMarkOff();

	void SetAttackAreaMark(bool Enable);

	void AddItem(class UBaseItem* Item);

	bool IsCanAddItem();

	void UnEquipHat();
	void UnEquipChest();
	void UnEquipPants();
	void UnEquipGlove();
	void UnEquipWeapon();
	
	const class UBaseItem* GetWeaponItem() const;
	const class UBaseItem* GetArmorItem(EArmorType ArmorType) const;

	void SetVisibleInteractionUI(bool Enable);

	void SetBoundState() { PlayerState = EPlayerState::Bound; }
	bool GetIsBound() const { return PlayerState == EPlayerState::Bound;; }

	FTransform GetSoulSiphonEffectPos() const;

	EPlayerState GetPlayerState() const { return PlayerState; }
	void SetNormalState();
	void SetPlayingLevelSequenceState();
	

	void SetTargetCameraRotation(const FRotator & Rotation) { TargetCameraRotation = Rotation; }
	void SetTargetCameraLocation(const FVector& Location) { TargetCameraLocation = Location; }
	void SetTargetArmLength(float ArmLength) { TargetArmLength = ArmLength; }
	void SetUpdateCameraTransform(bool Reverse = false);
	void SetCameraTransformSpeed(float Speed) { CameraTransformSpeed = Speed; }

	void SetJumpEndPoint(const FVector& Location) { JumpEndPoint = Location; }
	void JumpingStart();
	bool GetIsJumping() const { return IsJumping; }

	bool GetIsVisibleInteractionUI() const;
	void SetIsCameraShakeJump(bool IsShake) { IsCameraShakeJump = IsShake; }

	void RotateMouseDirectionTimeLineVersion();
	bool IsDead() const { return Dead; }

	void ResetState();
	void SetSlowState(bool Enable);

	void InitPhase3State();

	void UltimateEnd();
	void UltimateShot();
public:
	//장비 장착 함수
	//인자는 새로 장착할 아이템
	class UBaseItem* EquipItem(class UBaseItem* Item);

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
	void BasicAttackShot();
	//----------------------------------------------------

	//이동 스킬
	//----------------------------------------------------
	//이동 스킬 입력시 호출 함수
	void MoveSkillAction();

	//이동 스킬 Foot Decal생성
	void SpawnMoveSkillFootDecal();

	//이동 스킬 먼지 효과 제거
	void RemoveMoveSkillFootDirt();

	//이동 스킬 먼지 효과 생성
	void CreateMoveSkillFootDirt();
	//----------------------------------------------------

	//KickShotSkill
	void SpecialAttackShot();

	//FlippingSkill
	//----------------------------------------------------
	void FlippingShot1();
	void FlippingShot2();
	void FlippingShot3();
	//----------------------------------------------------

	//ArrowShowerSkill
	void ArrowShowerShot();

	//PulseShotSkill
	//----------------------------------------------------
	void PulseShot();

	//PulseShot 스킬 Foot Decal생성
	void SpawnPulseShotFootDecal();
	//----------------------------------------------------

public:
	//잔상 생성
	UFUNCTION(BlueprintCallable)
	void CreateAfterimage();

	//카메라 Shake 재생
	void PlayCameraShake();

	//Jump시 카메라 Shake재생
	void PlayJumpCameraShake();

	//카메라 ZoomOut 효과 재생
	void PlayCameraZoomOut(int StartSpringArmLength, float Speed);

	//SceneShatter효과 생성
	void CreateSceneShatter();

	//궁극기 시네마틱 재생
	void PlayUltimateSequence();

	UFUNCTION()
	void UltimateSequenceFinished();

private:
	//마우스 방향으로 회전하는 함수
	void RotateMouseDirection();

	//보스 방향으로 회전하는 함수
	void RotateBossDirection(float DeltaSecond);

	//보스 방향으로 회전할 때 회전 방향 계산 함수
	void ComputeRotateDirectionToBoss();

	void UpdateAttackTargetLocation();

	//Material초기화 함수
	void InitMaterial();

	//효과를 껐다 켰다할 EffectActor 초기화 함수
	void InitEffect();

	//마우스 방향으로 RotateSpeed만큼 회전하는 함수
	void AddRotateMouseDirection(float DeltaTime);

	//ZoomOut효과를 위한 SpringArm길이 Update함수
	void UpdateZoomOutEffect(float DeltaTime);

	void ApplyShatterForce();
	void DestroyShatterEffect();

	void UpdateCameraTransform(float DeltaTime);

	void DamageProc(float Damage);
	FVector GetRandomVector() const;

	void HideBlockMapComponent();
private:
	//카메라 관련 컴포넌트
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* QuarterViewCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SceneCapture, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* SceneCapture;
	//-----------------------------------------------------------------------------------------------

	//스킬 사거리 표시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SkillRangeMarkMesh;		//반지름 20짜리 실린더

	const float RangeMarkMeshScale = 0.0138f; //단위 size

	//----------------------------------------

	//스킬 관련 ActorComponent
	UPROPERTY(VisibleAnywhere, Category = Skill)
	class USkillManagerComponent* SkillManager;

	//인벤토리 ActorComponent
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	class UInventoryComponent* Inventory;

	//장비템 ActorComponent
	UPROPERTY(VisibleAnywhere, Category = Equip)
	class UEquipmentComponent* Equip;

	//Enhanced input system
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* MoveSkillInputAction;
	//-----------------------------------------------------------------------------------------------

	//UI
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* InteractionUI;
	//-----------------------------------------------------------------------------------------------


	//캐릭터 공격시 회전
	//-----------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMove, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* AttackRotationTimeline;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* RotationCurve;
	
	FOnTimelineFloat RotateTimelineProgress;

	FRotator TargetRotator;
	FRotator StartRotator;

	UFUNCTION()
	void UpdateRotation(float Alpha);

	bool IsCanRotate;
	//-----------------------------------------------------------------------------------------------

	UPROPERTY()
	class AArcherPlayerController* ArcherController;

	UPROPERTY()
	class UArcherAnimInstance* ArcherAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class ABow* Bow;

	UPROPERTY()
	TArray<UMaterialInstanceDynamic*> DynMaterialArr;

	UPROPERTY()
	class AMoveSkillFootDirt* FootDirtEffect;


private:
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


	//기본 공격 범위
	//--------------------------------------------
	const FVector BasicAttackBoxExtent = FVector(600.f,90.f,90.f);
	const float BasicAttackHeightOffset = 100.f;
	//--------------------------------------------

	//카메라 Shake
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCameraShakeBase> ArcherSkillCameraShakeClass;


	//Camera ZoomOut 효과
	//--------------------------------------------
	bool IsCameraZoomOut;

	float CurrentSpringArmLength = 0;
	float ZoomOutSpeed = 10;
	//--------------------------------------------

	UPROPERTY(EditAnywhere, Category = SceneShatter, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASceneShatter> SceneShatterClass;

	UPROPERTY(EditAnywhere, Category = SceneShatter, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ASceneShatterFieldSystemActor> FieldSystemActorClass;

	UPROPERTY(EditAnywhere, Category = SceneShatter, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> SceneShatterWidgetClass;

	UPROPERTY()
	class ASceneShatter* SceneShatter;

	UPROPERTY()
	class ASceneShatterFieldSystemActor* FieldSystemActor;

	UPROPERTY()
	UUserWidget* SceneShatterWidget;

	FTimerHandle ShatterCreateTimerHandle; //부수는 효과 적용
	FTimerHandle ShatterDestroyTimerHandle;//부수는 효과관련된 리소스 제거 
	
	EPlayerState PlayerState;

	bool RotateToBoss;
	const float KnockBackRotateSpeed = 360.f;
	short RotationDirectionToBoss;

	//연출용 카메라 위치, 회전 정보
	//--------------------------------------------
	const FRotator DefaultCameraRotation = FRotator(-45.0f, -45.0f, 0.0f);
	const float DefaultArmLength = 850.f;

	FRotator StartCameraRotation;
	FVector StartCameraLocation;
	float StartArmLength;
	FRotator TargetCameraRotation;
	FVector TargetCameraLocation;
	float TargetArmLength;

	bool IsUpdateCameraTransform; 
	float CameraTransformSpeed;
	float CurCameraTransformAlpha;
	//--------------------------------------------
	
	//점프용 캐릭터 위치
	//--------------------------------------------
	FVector JumpStartPoint;
	FVector JumpEndPoint;
	
	bool IsJumping;
	bool IsCameraShakeJump;

	UPROPERTY(EditDefaultsOnly)
	UCurveVector* JumpCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMove, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* JumpLocationTimeline;

	FOnTimelineVector JumpLocatoinTimelineProgress;

	UFUNCTION()
	void UpdateJumpLocation(FVector Alpha);

	UPROPERTY(EditDefaultsOnly)
	UCurveVector* CameraShakeJumpCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMove, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* CameraShakeJumpLocationTimeline;
	
	FOnTimelineVector CameraShakeJumpLocatoinTimelineProgress;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCameraShakeBase> ArcherJumpCameraShakeClass;

	FTimerHandle JumpCameraShakeTimerHandle;
	//--------------------------------------------

	//HP
	//--------------------------------------------
	float CurHP;
	float MaxHP;

	bool Dead;
	//--------------------------------------------

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class ULevelSequence* UltimateSequence;


	//Damage
	//--------------------------------------------
	const float BasicAttackBaseDamage = 200000;
	//--------------------------------------------

	//받은 Damage관련 변수
	//-----------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageText> DamageTextWidgetClass;

	const FVector DamageTextOffset = { 0.0f,-125.0f,60.0f };

	const float RandomVectorRange = 30;
	//-----------------------------------------------------------------------------

	UPROPERTY()
	class AHideMapComponent* TargetHideActor;
	bool IsLineTraceMapComponent;

	UPROPERTY()
	class ULevelSequencePlayer* UltimateSequencePlayer;

};
