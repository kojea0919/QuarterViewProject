// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAreaMarkEffect.h"
#include "Components/DecalComponent.h"
#include "Archer/ArcherPlayerController.h"

AAttackAreaMarkEffect::AAttackAreaMarkEffect()
	: ArcherController(nullptr), CurSkillRange(0)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SetActorRotation(FRotator(-90.0f, 0.0f, 0.0f));
}

void AAttackAreaMarkEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//액터가 스킬의 사거리를 넘어가지 못하게 만든다.
	FVector MousePos = ArcherController->GetMouseWorldLocation();
	FVector PlayerPos = ArcherController->GetCharacter()->GetActorLocation();

	//마우스와 플레이어의 거리가 사거리 안이면 그대로 생성
	double Length = (MousePos - PlayerPos).Length();
	if(Length <= CurSkillRange)
		SetActorLocation(MousePos);
	//사거리 밖이면 마우스 방향으로 사거리 만큼 위치에 생성한다.
	else
	{
		FVector PlayerToMouse = MousePos - PlayerPos;
		SetActorLocation(PlayerToMouse.GetSafeNormal() * CurSkillRange + PlayerPos);
	}
}

void AAttackAreaMarkEffect::LoadMaterial()
{
	UMaterialInstance* BaseDecalMaterial = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/Player/Archer/AttackAreaMark/M_AttackAreaMark_Inst.M_AttackAreaMark_Inst"));

	DynMaterial = UMaterialInstanceDynamic::Create(BaseDecalMaterial, this);
	Decal->SetDecalMaterial(DynMaterial);
}
