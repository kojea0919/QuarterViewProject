// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/SlotKey.h"
#include "ArcherPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AArcherPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AArcherPlayerController();

public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;
	
	//마우스의 월드 좌표 반환 함수
	FVector GetMouseWorldLocation();

	//Skill Quick Slot Key Setting
	void SetQuickSlotSkill(class UBaseSkill* Skill, ESkillQuickSlot SlotKey);

	void SetVisibilityIntersectionKey(bool Enable);

	//Skill Slot 바인드 함수
	//-------------------------------------------------
	void UseQSlot();
	void ReleaseQSlot();

	void UseWSlot();
	void ReleaseWSlot();

	void UseESlot();
	void ReleaseESlot();

	void UseRSlot();
	void ReleaseRSlot();

	void UseFSlot();
	void ReleaseFSlot();

	void UseDSlot();
	void ReleaseDSlot();
	//-------------------------------------------------

	void UseStopSequenceButton();

	void UseInventoryKey();
	void UseEquipmentKey();
	void UseInteractionKey();

	void UseBossTestKey(); //testcode

	class USkillGaugeBar* GetSkillGaugeBar() const;

	void SetAreaMarkEffectVisible(bool Enable);
	void SetAreaMarkEffectCurSkillRange(float Range);

	FVector GetAttakAreaMarkLocation() const;

	void SetupStoreUI(class AStoreNPC* Npc,class AArcher * TargetPlayer);

	class UInventory* GetInventory();
	class UEquipment* GetEquipment();

	void SetBoss(class ABoss* Boss);
	FVector GetBossLocation() const;

	void SetDisableInput();
	void SetEnableInput();

	void SetBossCurrentHP(float HP);
	void SetVisibleBossClearWindow();

	void SetPlayerCurrentHPRate(float Rate);

	void SetVisiblePlayerHUD(bool Enable);
	
	void SetIsPlayingLevelSequence(bool Enable) { IsPlayingLevelSequence = Enable; }
	void SetLevelSequencePlayer(class ULevelSequencePlayer* SequencePlayer) { CurLevelSequencePlayer = SequencePlayer; }

	void SetVisibleLevelSequenceHUD(bool Enable);

	void PlayLevelSequence(class ULevelSequencePlayer* SequencePlayer);
	void StopLevelSequence();

	void SetVisiblePlayerDeadHUD(bool Enable);
	void PlayerDead();

	void ResetPlayerAndBoss();
	void StopPlayerSlow();

	void RemoveMouseReverse() { IsMouseReverseState = false; }

	//void SetVisibleCircleFadeOut(bool Enable);
	//void PlayCircleFadeOut();

private:
	//마우스 입력시 마우스 포인터 방향으로 이동하는 함수
	//-------------------------------------------------
	void MoveTargetAction();
	void MoveTargetActionStart();
	void MoveTarget(FVector TargetLocation);
	//-------------------------------------------------

	void InitHUD();

	void CheckMousePositionCollision();

private:
	//Player HUD
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class UPlayerHUD> PlayerHUDWidgetClass;

	class UPlayerHUD* PlayerHUD;
	//-------------------------------------------------

	//LevelSequence HUD
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class UUserWidget> LevelSequenceHUDWidgetClass;

	class UUserWidget* LevelSequenceHUD;
	//-------------------------------------------------

	//Fail UI
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class UPlayerDeadHUD> PlayerDeadHUDWidgetClass;

	class UPlayerDeadHUD* PlayerDeadHUD;
	//-------------------------------------------------

	////CircleFadeOut
	////-------------------------------------------------
	//UPROPERTY(EditAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	//TSubclassOf<class UCircleFadeOutHUD> CircleFadeOutWidgetClass;

	//class UCircleFadeOutHUD* CircleFadeOut;
	////-------------------------------------------------

	//QuickSlot Key 관련 InputAction
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotQInputAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotWInputAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotEInputAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotRInputAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotDInputAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SlotFInputAction;
	//-------------------------------------------------

	//인벤토리 키 InputAction
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* InventoryKeyInputAction;

	//장비창 키 InputAction
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* EquipmentKeyInputAction;

	//상호작용 키 InputAction
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* InteractionInputAction;

	//연출 스탑 키 InputAction
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SequenceStopInputAction;

	//이동키
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* MoveTargetInputAction;

	//testcode
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* BossTestKey;

	UPROPERTY(VisibleAnywhere)
	class AAttackAreaMarkEffect* AreaMarkEffect;

	bool IsSetStoreNPC;		//현재 Store에 NPC가 배정이 됐는지 나타내는 변수

	//보스
	class ABoss* CurrentBoss;
	bool BossRenderOutLine;

	const float MouseCollisionSearchRange = 5000.f;

	//LevelSequence관련 변수
	//-----------------------------------------------
	bool IsPlayingLevelSequence;

	class ULevelSequencePlayer* CurLevelSequencePlayer;
	//-----------------------------------------------


	bool IsMouseReverseState;

	///클릭 이펙트
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = " true"))
	class UNiagaraSystem* MouseClickEffect;
};
