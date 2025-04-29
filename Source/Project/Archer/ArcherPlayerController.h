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
	//-------------------------------------------------

	void UseInventoryKey();
	void UseEquipmentKey();
	void UseInteractionKey();

	class USkillGaugeBar* GetSkillGaugeBar() const;

	void SetAreaMarkEffectVisible(bool Enable);
	void SetAreaMarkEffectCurSkillRange(float Range);

	FVector GetAttakAreaMarkLocation() const;

	void SetupStoreUI(class AStoreNPC* Npc,class AArcher * TargetPlayer);

	class UInventory* GetInventory();
	class UEquipment* GetEquipment();
	
	void SetFocusWidget(UUserWidget* Widget);

private:
	//마우스 입력시 마우스 포인터 방향으로 이동하는 함수
	//-------------------------------------------------
	void MoveTargetAction();
	void MoveTarget(FVector TargetLocation);
	//-------------------------------------------------

	void InitPlayerHUD();

private:
	//Player HUD
	//-------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = HUD, meta = (AllowPrivateAccess = " true"))
	TSubclassOf<class UPlayerHUD> PlayerHUDWidgetClass;

	class UPlayerHUD* PlayerHUD;
	//-------------------------------------------------

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

	UPROPERTY(VisibleAnywhere)
	class AAttackAreaMarkEffect* AreaMarkEffect;

	bool IsSetStoreNPC;		//현재 Store에 NPC가 배정이 됐는지 나타내는 변수

	//현재 포커스 중인 UI
	//-------------------------------------
	UUserWidget* CurrentFocusWidget;

	const int PrevZOrder = 4;
	const int FocusZOrder = 5;
	
	//-------------------------------------

};
