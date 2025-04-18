// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManagerComponent.h"
#include "Project/Archer/Archer.h"
#include "Project/Archer/ArcherPlayerController.h"
#include "Project/Archer/Animation/ArcherAnimInstance.h"
#include "ArcherSkillDesperado.h"

USkillManagerComponent::USkillManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USkillManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void USkillManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USkillManagerComponent::Init()
{
	AArcher* Archer = Cast<AArcher>(GetOwner());
	if (nullptr == Archer)
		return;

	UArcherAnimInstance* Anim = Cast<UArcherAnimInstance>(Archer->GetMesh()->GetAnimInstance());
	if (nullptr == Anim)
		return;

	AArcherPlayerController* PlayerController = Cast<AArcherPlayerController>(Archer->GetController());
	if (nullptr == PlayerController)
		return;

	//Desperado Setting
	//---------------------------------------------------------
	UArcherSkillDesperado* Desperado = NewObject<UArcherSkillDesperado>();
	SkillArr.Push(Desperado);
	Desperado->SetAnimInstance(Anim);					//UseSkill하면 Montage를 재생해줄 AnimInstance설정
	Desperado->SetMontage(Anim->GetDesperadoMontage());	//재생할 스킬 Montage설정
	Desperado->SetBaseClass(Archer);
	Desperado->SetQuickSlotKey(ESkillQuickSlot::SlotQ);	//초기 QuickSlotKey 설정
	Desperado->SetMaterial(TEXT("/Script/Engine.Material'/Game/Player/UI/Skill/M_Desperado.M_Desperado"));

	PlayerController->SetQuickSlotSkill(Desperado, ESkillQuickSlot::SlotQ);
	//---------------------------------------------------------

}

UBaseSkill* USkillManagerComponent::GetSkill(uint8 SkillType)
{
	if (SkillType >= SkillArr.Num())
		return nullptr;

	return SkillArr[SkillType];
}

