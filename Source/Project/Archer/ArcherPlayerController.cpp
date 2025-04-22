// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherPlayerController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Project/Archer/Archer.h"
#include "Project/UI/PlayerHUD.h"
#include "EnhancedInputComponent.h"

AArcherPlayerController::AArcherPlayerController()
	: PlayerHUD(nullptr)
{
	static ConstructorHelpers::FClassFinder<UPlayerHUD> UI_PLAYERHUD_C(TEXT("/Game/Player/UI/UI_PlayerHUD.UI_PlayerHUD_C"));
	if (UI_PLAYERHUD_C.Succeeded())
		PlayerHUDWidgetClass = UI_PLAYERHUD_C.Class;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTQ_INPUTACTION(TEXT("/Game/Player/Input/IA_UseQuickSlotQ.IA_UseQuickSlotQ"));
	if (IA_SLOTQ_INPUTACTION.Succeeded())
		SlotQInputAction = IA_SLOTQ_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTW_INPUTACTION(TEXT("/Game/Player/Input/IA_UseQuickSlotW.IA_UseQuickSlotW"));
	if (IA_SLOTW_INPUTACTION.Succeeded())
		SlotWInputAction = IA_SLOTW_INPUTACTION.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_SLOTE_INPUTACTION(TEXT("/Game/Player/Input/IA_UseQuickSlotE.IA_UseQuickSlotE"));
	if (IA_SLOTE_INPUTACTION.Succeeded())
		SlotEInputAction = IA_SLOTE_INPUTACTION.Object;
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

	InitPlayerHUD();
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
	}


	InputComponent->BindAction(TEXT("MoveTarget"), IE_Pressed, this, &AArcherPlayerController::MoveTargetAction);
}

void AArcherPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AArcherPlayerController::MoveTargetAction()
{
	//현재 캐릭터가 이동 가능 상태가 아니면 return
	AArcher* Archer = Cast<AArcher>(GetCharacter());
	if (!Archer->GetMoveAble())
		return;

	//마우스 클릭 위치를 월드 좌표로
	FVector TargetLocation = GetMouseWorldLocation();

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

void AArcherPlayerController::InitPlayerHUD()
{
	if (PlayerHUDWidgetClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(this,PlayerHUDWidgetClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
		}
	}
}

FVector AArcherPlayerController::GetMouseWorldLocation()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	return HitResult.Location;
}

void AArcherPlayerController::SetQuickSlotSkill(UBaseSkill* Skill, ESkillQuickSlot SlotKey)
{
	if (PlayerHUD)
	{
		PlayerHUD->SetQuickSlotSkill(Skill, SlotKey);
	}
}

void AArcherPlayerController::UseQSlot()
{
	if (PlayerHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("q"));
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
