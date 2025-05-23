// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherPlayerController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Archer/Archer.h"
#include "UI/PlayerHUD.h"
#include "EnhancedInputComponent.h"
#include "UI/SkillGaugeBar.h"
#include "UI/Inventory.h"
#include "Archer/Effect/AttackAreaMarkEffect.h"
#include "Monster/Boss.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "WorldSubSystem/BossBattleSubSystem.h"
#include "UI/PlayerEndHUD.h"
#include "GamePlayEffect/Sky/Sky.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GamePlayEffect/BGMManager/BGMManager.h"
//#include "UI/CircleFadeOutHUD.h"

AArcherPlayerController::AArcherPlayerController()
	: PlayerHUD(nullptr), IsSetStoreNPC(false), BossRenderOutLine(false), IsPlayingLevelSequence(false), CurLevelSequencePlayer(nullptr),
	IsMouseReverseState(false),BGMManager(nullptr)
{
	static ConstructorHelpers::FClassFinder<UPlayerHUD> UI_PLAYERHUD_C(TEXT("/Game/GamePlay/Player/UI/UI_PlayerHUD.UI_PlayerHUD_C"));
	if (UI_PLAYERHUD_C.Succeeded())
		PlayerHUDWidgetClass = UI_PLAYERHUD_C.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_LEVELSEQUENCEHUD_C(TEXT("/Game/GamePlay/Player/UI/UI_LevelSequenceHUD.UI_LevelSequenceHUD_C"));
	if (UI_LEVELSEQUENCEHUD_C.Succeeded())
		LevelSequenceHUDWidgetClass = UI_LEVELSEQUENCEHUD_C.Class;

	static ConstructorHelpers::FClassFinder<UPlayerEndHUD> UI_PLAYERDEADHUD_C(TEXT("/Game/GamePlay/Player/UI/UI_PlayerEndHUD.UI_PlayerEndHUD_C"));
	if (UI_PLAYERDEADHUD_C.Succeeded())
		PlayerEndHUDWidgetClass = UI_PLAYERDEADHUD_C.Class;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTQ_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotQ.IA_UseQuickSlotQ"));
	if (IA_SLOTQ_INPUTACTION.Succeeded())
		SlotQInputAction = IA_SLOTQ_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTW_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotW.IA_UseQuickSlotW"));
	if (IA_SLOTW_INPUTACTION.Succeeded())
		SlotWInputAction = IA_SLOTW_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTE_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotE.IA_UseQuickSlotE"));
	if (IA_SLOTE_INPUTACTION.Succeeded())
		SlotEInputAction = IA_SLOTE_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTR_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotR.IA_UseQuickSlotR"));
	if (IA_SLOTR_INPUTACTION.Succeeded())
		SlotRInputAction = IA_SLOTR_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTS_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotS.IA_UseQuickSlotS"));
	if (IA_SLOTS_INPUTACTION.Succeeded())
		SlotSInputAction = IA_SLOTS_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTD_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotD.IA_UseQuickSlotD"));
	if (IA_SLOTD_INPUTACTION.Succeeded())
		SlotDInputAction = IA_SLOTD_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTF_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_UseQuickSlotF.IA_UseQuickSlotF"));
	if (IA_SLOTF_INPUTACTION.Succeeded())
		SlotFInputAction = IA_SLOTF_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_INVENTORY_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_Inventory.IA_Inventory"));
	if (IA_INVENTORY_INPUTACTION.Succeeded())
		InventoryKeyInputAction = IA_INVENTORY_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_EQUIPMENT_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_Equipment.IA_Equipment"));
	if (IA_EQUIPMENT_INPUTACTION.Succeeded())
		EquipmentKeyInputAction = IA_EQUIPMENT_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_INTERACTION_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_Interaction.IA_Interaction"));
	if (IA_INTERACTION_INPUTACTION.Succeeded())
		InteractionInputAction = IA_INTERACTION_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_STOPSEQUENCE_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_StopSequence.IA_StopSequence"));
	if (IA_STOPSEQUENCE_INPUTACTION.Succeeded())
		SequenceStopInputAction = IA_STOPSEQUENCE_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVETARGET_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_MoveTarget.IA_MoveTarget"));
	if (IA_MOVETARGET_INPUTACTION.Succeeded())
		MoveTargetInputAction = IA_MOVETARGET_INPUTACTION.Object;

	//testcode
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_BOSSTESTKEY_INPUTACTION(TEXT("/Game/GamePlay/Player/Input/IA_BossTestKey.IA_BossTestKey"));
	if (IA_BOSSTESTKEY_INPUTACTION.Succeeded())
		BossTestKey = IA_BOSSTESTKEY_INPUTACTION.Object;

}

void AArcherPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//입력 모드 설정
	//-------------------------------------------
	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	//-------------------------------------------

	AreaMarkEffect = GetWorld()->SpawnActor<AAttackAreaMarkEffect>(AAttackAreaMarkEffect::StaticClass());
	AreaMarkEffect->SetController(this);
	AreaMarkEffect->SetHidden(true);

	InitHUD();
	
}

void AArcherPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SlotQInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseQSlot);
		EnhancedInputComponent->BindAction(SlotQInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseQSlot);

		EnhancedInputComponent->BindAction(SlotWInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseWSlot);
		EnhancedInputComponent->BindAction(SlotWInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseWSlot);

		EnhancedInputComponent->BindAction(SlotEInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseESlot);
		EnhancedInputComponent->BindAction(SlotEInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseESlot);

		EnhancedInputComponent->BindAction(SlotRInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseRSlot);
		EnhancedInputComponent->BindAction(SlotRInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseRSlot);

		EnhancedInputComponent->BindAction(SlotDInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseDSlot);
		EnhancedInputComponent->BindAction(SlotDInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseDSlot);

		EnhancedInputComponent->BindAction(SlotFInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseFSlot);
		EnhancedInputComponent->BindAction(SlotFInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseFSlot);

		EnhancedInputComponent->BindAction(SlotSInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseSSlot);
		EnhancedInputComponent->BindAction(SlotSInputAction, ETriggerEvent::Completed, this, &AArcherPlayerController::ReleaseSSlot);

		EnhancedInputComponent->BindAction(SequenceStopInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseStopSequenceButton);
		
		EnhancedInputComponent->BindAction(InventoryKeyInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseInventoryKey);
		EnhancedInputComponent->BindAction(EquipmentKeyInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseEquipmentKey);
		EnhancedInputComponent->BindAction(InteractionInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseInteractionKey);
		
		EnhancedInputComponent->BindAction(MoveTargetInputAction, ETriggerEvent::Triggered, this, &AArcherPlayerController::MoveTargetAction);
		EnhancedInputComponent->BindAction(MoveTargetInputAction, ETriggerEvent::Started, this, &AArcherPlayerController::MoveTargetActionStart);

		EnhancedInputComponent->BindAction(BossTestKey, ETriggerEvent::Triggered, this, &AArcherPlayerController::UseBossTestKey);//testcode
	}

}

void AArcherPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CheckMousePositionCollision();
}

void AArcherPlayerController::MoveTargetAction()
{
	//현재 캐릭터가 이동 가능 상태가 아니면 return
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (!Archer->GetMoveAble() || Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	//마우스 클릭 위치를 월드 좌표로
	FVector TargetLocation = GetMouseWorldLocation();

	//해당 위치로 이동
	MoveTarget(TargetLocation);
}

void AArcherPlayerController::MoveTargetActionStart()
{
	//현재 캐릭터가 이동 가능 상태가 아니면 return
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (!Archer->GetMoveAble() || Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	//마우스 클릭 위치를 월드 좌표로
	FVector TargetLocation = GetMouseWorldLocation();

	if (MouseClickEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			MouseClickEffect,
			TargetLocation,
			FRotator(),
			FVector(1.5f)
		);
	}
	//해당 위치로 이동
	MoveTarget(TargetLocation);
}

void AArcherPlayerController::MoveTarget(FVector TargetLocation)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, TargetLocation);
}

void AArcherPlayerController::InitHUD()
{
	if (PlayerHUDWidgetClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(this,PlayerHUDWidgetClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();

			if (CurrentBoss)
			{
				PlayerHUD->SetBossMaxHP(CurrentBoss->GetMaxHP());
				PlayerHUD->InitBossHP();
			}
		}
	}

	if (LevelSequenceHUDWidgetClass)
	{		
		LevelSequenceHUD = CreateWidget<UUserWidget>(this, LevelSequenceHUDWidgetClass);
		if (LevelSequenceHUD)
		{
			LevelSequenceHUD->AddToViewport();
			LevelSequenceHUD->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (PlayerEndHUDWidgetClass)
	{
		PlayerEndHUD = CreateWidget<UPlayerEndHUD>(this, PlayerEndHUDWidgetClass);
		if (PlayerEndHUD)
		{
			PlayerEndHUD->AddToViewport();
			PlayerEndHUD->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	/*if (CircleFadeOutWidgetClass)
	{
		CircleFadeOut = CreateWidget<UCircleFadeOutHUD>(this, CircleFadeOutWidgetClass);
		if (CircleFadeOut)
		{
			CircleFadeOut->AddToViewport();
			CircleFadeOut->SetVisibility(ESlateVisibility::Hidden);
		}
	}*/
}

void AArcherPlayerController::CheckMousePositionCollision()
{
	FVector WorldLocation, WorldDirection;
	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = WorldLocation + MouseCollisionSearchRange * WorldDirection;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End,
			ECollisionChannel::ECC_GameTraceChannel2, Params))
		{
			AActor* HitActor = HitResult.GetActor();
			ABoss* Boss = Cast<ABoss>(HitActor);
			if (Boss && !BossRenderOutLine)
			{
				Boss->SetOutLineEnable(true);
				BossRenderOutLine = true;
			}
		}
		else if(BossRenderOutLine)
		{
			CurrentBoss->SetOutLineEnable(false);
			BossRenderOutLine = false;
		}
	}
}

FVector AArcherPlayerController::GetMouseWorldLocation()
{
	FHitResult HitResult;
	FVector TargetLocation;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		TargetLocation = HitResult.Location;

		//마우스 반전상태면 플레이러를 기준으로 대칭이동 후 반환
		//------------------------------------------------------
		if (IsMouseReverseState)
		{
			FVector TargetToPlayerVector = GetCharacter()->GetActorLocation() - TargetLocation;

			TargetLocation = TargetToPlayerVector + GetCharacter()->GetActorLocation();
			TargetLocation.Z = GetCharacter()->GetActorLocation().Z - 90.0f;
		}
		//------------------------------------------------------
	}

	return TargetLocation;
}

void AArcherPlayerController::SetQuickSlotSkill(UBaseSkill* Skill, ESkillQuickSlot SlotKey)
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->SetQuickSlotSkill(Skill, SlotKey);
	}
}

void AArcherPlayerController::SetVisibilityIntersectionKey(bool Enable)
{
	if (PlayerHUD)
	{
		PlayerHUD->SetVisibilityIntersectionKey(Enable);
	}
}

void AArcherPlayerController::UseQSlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotQ);
	}
}

void AArcherPlayerController::ReleaseQSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotQ);
	}
}

void AArcherPlayerController::UseWSlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotW);
	}
}

void AArcherPlayerController::ReleaseWSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotW);
	}
}

void AArcherPlayerController::UseESlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotE);
	}
}

void AArcherPlayerController::ReleaseESlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotW);
	}
}

void AArcherPlayerController::UseRSlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotR);
	}
}

void AArcherPlayerController::ReleaseRSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotR);
	}
}

void AArcherPlayerController::UseFSlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotF);
	}
}

void AArcherPlayerController::ReleaseFSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotF);
	}
}

void AArcherPlayerController::UseDSlot()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer->GetPlayerState() != EPlayerState::Normal)
		return;

	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotD);
	}
}

void AArcherPlayerController::ReleaseDSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotD);
	}
}

void AArcherPlayerController::UseSSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->UseSkill(ESkillQuickSlot::SlotS);
	}
}

void AArcherPlayerController::ReleaseSSlot()
{
	if (PlayerHUD)
	{
		PlayerHUD->ReleaseSkill(ESkillQuickSlot::SlotS);
	}
}

void AArcherPlayerController::UseStopSequenceButton()
{
	if (IsPlayingLevelSequence && CurLevelSequencePlayer)
	{
		CurLevelSequencePlayer->Stop();
	
		StopLevelSequence();
	}
}

void AArcherPlayerController::UseInventoryKey()
{
	if (PlayerHUD)
	{
		PlayerHUD->SetVisibilityInventory();
	}
}

void AArcherPlayerController::UseEquipmentKey()
{
	if (PlayerHUD)
	{
		PlayerHUD->SetVisibilityEquipment();
	}
}

void AArcherPlayerController::UseInteractionKey()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (!Archer->GetIsVisibleInteractionUI())
	{
		return;
	}

	if (PlayerHUD)
	{
		/*if(IsSetStoreNPC)
			PlayerHUD->SetVisibilityStore();*/

		

	}

	if (Archer)
	{
		Archer->JumpingStart();
	}
}

void AArcherPlayerController::UseBossTestKey()
{
	if (CurrentBoss)
	{
		CurrentBoss->StartBehaviorTree();
	}
}

USkillGaugeBar* AArcherPlayerController::GetSkillGaugeBar() const
{
	if(PlayerHUD)
		return PlayerHUD->GetSkillGaugeBar();
	return nullptr;
}

void AArcherPlayerController::SetAreaMarkEffectVisible(bool Enable)
{
	if (AreaMarkEffect)
		AreaMarkEffect->SetActorHiddenInGame(!Enable);
}

void AArcherPlayerController::SetAreaMarkEffectCurSkillRange(float Range)
{
	if (AreaMarkEffect)
		AreaMarkEffect->SetCurSkillRange(Range);
}

FVector AArcherPlayerController::GetAttakAreaMarkLocation() const
{
	return AreaMarkEffect->GetActorLocation();
}

void AArcherPlayerController::SetupStoreUI(AStoreNPC* Npc,AArcher * TargetPlayer)
{
	if (nullptr == Npc)
		IsSetStoreNPC = false;
	else
		IsSetStoreNPC = true;
	
	if(PlayerHUD)
		PlayerHUD->SetupStoreUI(Npc, TargetPlayer);
}

UInventory* AArcherPlayerController::GetInventory()
{
	if (nullptr == PlayerHUD)
		return nullptr;
	return PlayerHUD->GetInventory();
}

UEquipment* AArcherPlayerController::GetEquipment()
{
	if (nullptr == PlayerHUD)
		return nullptr;
	return PlayerHUD->GetEquipment();
}

void AArcherPlayerController::SetBoss(ABoss* Boss)
{
	if (Boss) 
		CurrentBoss = Boss; 

	if (PlayerHUD)
	{
		PlayerHUD->SetBossMaxHP(Boss->GetMaxHP());
		PlayerHUD->SetBossCurrentHP(Boss->GetCurrentHP());
	}
}

FVector AArcherPlayerController::GetBossLocation() const
{
	if (CurrentBoss)
		return CurrentBoss->GetActorLocation();

	return FVector();
}

void AArcherPlayerController::SetDisableInput()
{
	DisableInput(this);
}

void AArcherPlayerController::SetEnableInput()
{
	EnableInput(this);
}

void AArcherPlayerController::SetBossCurrentHP(float HP)
{
	if (PlayerHUD)
	{
		PlayerHUD->SetBossCurrentHP(HP);
	}
}

void AArcherPlayerController::SetVisibleBossClearWindow()
{
	if (PlayerHUD)
	{
		PlayerHUD->SetVisibilityBossClear(true);
	}
}

void AArcherPlayerController::SetPlayerCurrentHPRate(float Rate)
{
	if (PlayerHUD)
	{
		PlayerHUD->SetPlayerCurrentHPRate(Rate);
	}
}

void AArcherPlayerController::SetVisiblePlayerHUD(bool Enable)
{
	if (nullptr == PlayerHUD)
		return;

	if (Enable)
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AArcherPlayerController::SetVisibleLevelSequenceHUD(bool Enable)
{
	if (nullptr == LevelSequenceHUD)
		return;

	if (Enable)
	{
		LevelSequenceHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LevelSequenceHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AArcherPlayerController::PlayLevelSequence(ULevelSequencePlayer* SequencePlayer)
{
	if (CurrentBoss)
		CurrentBoss->SetActorLocation(FVector(0.0f, 0.0f, 0.0f));

	if (BGMManager)
		BGMManager->StopBGM();
	

	SetVisiblePlayerHUD(false);
	SetIsPlayingLevelSequence(true);
	CurLevelSequencePlayer = SequencePlayer;
	SetVisibleLevelSequenceHUD(true);
}

void AArcherPlayerController::StopLevelSequence()
{
	CurLevelSequencePlayer = nullptr;
	IsPlayingLevelSequence = false;
	CurLevelSequencePlayer = nullptr;

	SetVisiblePlayerHUD(true);
	SetVisibleLevelSequenceHUD(false);

	//보스 소환
	UBossBattleSubSystem * BossBattleSubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
	if (nullptr == BossBattleSubSystem)
	{
		return;
	}

	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer)
	{
		Archer->SetNormalState();
	}

	FTransform BossTransform = BossBattleSubSystem->GetBossSpawnTransform();
	if (CurrentBoss)
	{
		CurrentBoss->SetActorTransform(BossTransform);
		CurrentBoss->SetActorHiddenInGame(false);

		if (CurrentBoss->GetCurrentPhase() == 1)
		{
			if (BGMManager)
				BGMManager->PlayPhase1BGM();
		}

		else if (CurrentBoss->GetCurrentPhase() == 2)
		{
			if (BGMManager)
			{
				if (!BGMManager->IsPlayingBGM())
				{
					BGMManager->PlayPhase2BGM();
				}
			}

			BossBattleSubSystem->SetPhase2Light();

			CurrentBoss->SetStartPhase2();
		}

		else if (CurrentBoss->GetCurrentPhase() == 3)
		{
			if (BGMManager)
				BGMManager->PlayPhase3BGM();

			//마우스 반전
			IsMouseReverseState = true;

			CurrentBoss->SetStartPhase3();
			Archer->InitPhase3State();

			Archer->SetActorTransform(BossBattleSubSystem->GetPhase3PlayerTransform());
			CurrentBoss->SetActorTransform(BossBattleSubSystem->GetPhase3BossTransform());
		}

		else if (CurrentBoss->GetCurrentPhase() == 4)
		{
			return;
		}
	
		//BosHPBarUI On
		if (PlayerHUD)
		{
			if (CurrentBoss->GetCurrentPhase() == 1)
				PlayerHUD->InitBossHP();
			PlayerHUD->SetVisibilityBossHPBar(true);	
		}
	}


}

void AArcherPlayerController::SetVisiblePlayerEndHUD(bool Enable)
{
	if (PlayerEndHUD)
	{
		if(Enable)
			PlayerEndHUD->SetVisibility(ESlateVisibility::Visible);
		else
			PlayerEndHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AArcherPlayerController::PlayerDead()
{
	if (PlayerEndHUD)
	{
		PlayerEndHUD->SetVisibility(ESlateVisibility::Visible);
		PlayerEndHUD->PlayTextAnimation();
	}


	if (CurrentBoss)
	{
		CurrentBoss->PlayerDead();
	}
}

void AArcherPlayerController::ResetPlayerAndBoss()
{
	if (PlayerEndHUD)
		PlayerEndHUD->SetVisibility(ESlateVisibility::Hidden);

	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer)
	{
		UBossBattleSubSystem* BossBattleSubSystem = GetWorld()->GetSubsystem<UBossBattleSubSystem>();
		const FTransform & RespawnTransform =  BossBattleSubSystem->GetPlayerRespawnTransform();

		Archer->ResetState();
		Archer->SetActorTransform(RespawnTransform);

		BossBattleSubSystem->ResetSequence();
		BossBattleSubSystem->ResetSky();
		BossBattleSubSystem->ResetLight();
	}

	if (PlayerHUD)
	{
		PlayerHUD->SetPlayerCurrentHPRate(1.0f);
		PlayerHUD->SetVisibilityBossHPBar(false);
		PlayerHUD->SetVisibilityBossClear(false);
	}

	if (CurrentBoss)
		CurrentBoss->ResetState();


	IsMouseReverseState = false;
}

void AArcherPlayerController::StopPlayerSlow()
{
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (Archer)
	{
		Archer->SetSlowState(false);
	}
}

void AArcherPlayerController::StartedUltimateSequence()
{
	if (CurrentBoss)
		CurrentBoss->SetStunState();
}
//void AArcherPlayerController::SetVisibleCircleFadeOut(bool Enable)
//{
//	if (CircleFadeOut)
//	{
//		if (Enable)
//			CircleFadeOut->SetVisibility(ESlateVisibility::Visible);
//		else
//			CircleFadeOut->SetVisibility(ESlateVisibility::Hidden);
//	}
//}
//
//void AArcherPlayerController::PlayCircleFadeOut()
//{
//	if (CircleFadeOut)
//	{
//		CircleFadeOut->SetVisibility(ESlateVisibility::Visible);
//		CircleFadeOut->PlayCircleFadeOut();
//	}
//}
