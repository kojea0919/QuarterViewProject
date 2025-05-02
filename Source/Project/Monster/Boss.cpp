// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Boss.h"
#include "Engine/DamageEvents.h"
#include "DamageType/ArcherDamageType.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Monster/Effect/BasicHitEffect.h"
#include "UI/DamageText.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;

}

float ABoss::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UArcherDamageType* DamageType = nullptr;
	if (DamageEvent.DamageTypeClass)
	{
		DamageType = DamageEvent.DamageTypeClass->GetDefaultObject<UArcherDamageType>();
	}
	
	if (nullptr == DamageType)
		return 0;

	switch (DamageType->GetDamageType())
	{
	case EArcherDamageType::Basic:
		BasicTypeDamageProc();
		break;
	}


	return 0.0f;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss::BasicTypeDamageProc()
{
	UEffectObjectPool* EffectObjectPool = GetWorld()->GetSubsystem<UEffectObjectPool>();
	if (nullptr == EffectObjectPool)
		return;

	ABasicHitEffect* HitEffect = EffectObjectPool->GetBasicHitEffect();

	FTransform TargetTransform = GetActorTransform();
	TargetTransform.SetScale3D(FVector(3.0f));

	HitEffect->SpwanNiagaraEffect(TargetTransform);

	UDamageText * DamageText = CreateWidget<UDamageText>(GetWorld(), DamageTextWidgetClass);
	if (DamageText)
	{
		DamageText->AddToViewport();
		DamageText->SetDamageText(1000000);

		//데미지 Text위치 지정
		//------------------------------------
		FVector2D ScreenPos;
		FVector UILocation = GetActorLocation() + DamageTextOffset + GetRandomVector();

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (nullptr == PlayerController)
			return;

		UGameplayStatics::ProjectWorldToScreen(PlayerController, UILocation, ScreenPos);
		DamageText->SetPlayerController(PlayerController);
		DamageText->SetOwnerLocation(UILocation);

		/*float DPIScale = UWidgetLayoutLibrary::GetViewportScale(PlayerController);
		ScreenPos /= DPIScale;
		UE_LOG(LogTemp, Warning, TEXT("%f"), DPIScale);*/

		DamageText->SetPositionInViewport(ScreenPos);
		DamageText->PlayBasicDamageTextAnimation();
		//------------------------------------
	}

}

FVector ABoss::GetRandomVector()
{
	FVector ReturnVector; 
	float Range = RandomVectorRange;
	ReturnVector.X = FMath::RandRange(-Range, Range);
	ReturnVector.Y = FMath::RandRange(-Range, Range);
	ReturnVector.Z = FMath::RandRange(-Range, Range);
	return ReturnVector;
}

