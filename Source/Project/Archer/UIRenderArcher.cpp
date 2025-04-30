// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer/UIRenderArcher.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/CapsuleComponent.h"
#include "Engine/TextureRenderTarget2D.h"

AUIRenderArcher::AUIRenderArcher()
{
	PrimaryActorTick.bCanEverTick = true;

	//Components Create
	//---------------------------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SCENECAPTURE"));

	RenderTarget = NewObject<UTextureRenderTarget2D>();
	RenderTarget->InitAutoFormat(512, 512);
	RenderTarget->UpdateResourceImmediate(true);

	SceneCapture->TextureTarget = RenderTarget;
	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	//---------------------------------------------

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_ARCHER(TEXT("/Game/Player/Archer/Mesh/Player.Player"));
	if (SK_ARCHER.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_ARCHER.Object);
	}


	SpringArm->SetupAttachment(GetCapsuleComponent());
	SceneCapture->SetupAttachment(SpringArm);
}
void AUIRenderArcher::BeginPlay()
{
	Super::BeginPlay();


	SceneCapture->ShowOnlyActors.Add(*this);
}

void AUIRenderArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIRenderArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

