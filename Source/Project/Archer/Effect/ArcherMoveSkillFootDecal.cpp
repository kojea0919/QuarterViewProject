// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherMoveSkillFootDecal.h"
#include "Components/DecalComponent.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AArcherMoveSkillFootDecal::AArcherMoveSkillFootDecal()
	: CurRate(1.0f), CurOpacity(1.0f), StopUpdateRate(false)
{
	PrimaryActorTick.bCanEverTick = true;

	Decal->SetRelativeLocation(FVector(230.0f, 0.0f, 0.0f));
	//Decal->SetWorldRotation(FRotator(-90.0f, 90.0f + 90.0f, 0.0f));
	Decal->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));
	//Decal->SetWorldScale3D(FVector(0.09f, -0.08f, 0.80f));
	Decal->SetWorldScale3D(FVector(0.09f, -0.08f, 0.60f));
}

void AArcherMoveSkillFootDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFootDecal(DeltaTime);
}

void AArcherMoveSkillFootDecal::SetDecalRotation(FRotator Rotator)
{
	//Decal->SetWorldRotation(FRotator(-90.0f, 90.0f + 90.0f, 0.0f) + Rotator);
	Decal->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f) + Rotator);
}

void AArcherMoveSkillFootDecal::BeginPlay()
{
	Super::BeginPlay();
}

void AArcherMoveSkillFootDecal::LoadMaterial()
{
	UMaterialInstance* BaseDecalMaterial = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Player/Archer/Effect/MoveSkillDecal/M_FootFrictionMark_Inst.M_FootFrictionMark_Inst"));

	DynMaterial = UMaterialInstanceDynamic::Create(BaseDecalMaterial, this);
	Decal->SetDecalMaterial(DynMaterial);

	DynMaterial->SetScalarParameterValue(TEXT("Rate"), CurRate);
}

void AArcherMoveSkillFootDecal::UpdateFootDecal(float DeltaTime)
{
	if (!StopUpdateRate)
	{
		//보여지는 비율 Update
		//---------------------------------------------
		CurRate -= DeltaTime * 1.4f;

		if (CurRate > 0.0f)
		{
			DynMaterial->SetScalarParameterValue(FName("Rate"), CurRate);
			return;
		}
		//--------------------------------------------
	}

	//Opacity값 조절 시작
	//--------------------------------------------
	CurOpacity -= DeltaTime / 3.0f;
	if (CurOpacity <= 0.0f)
	{
		EffectObjPool->ReturnArcherMoveSkillFootDecal(this);
		CurOpacity = 1.0f;
		CurRate = 1.0f;

		StopUpdateRate = false;
	}

	DynMaterial->SetScalarParameterValue(FName("Opacity"), CurOpacity);
	//--------------------------------------------
}
