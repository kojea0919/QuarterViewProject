// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManagerComponent.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"
#include "Archer/Animation/ArcherAnimInstance.h"
#include "ArcherSkillDesperado.h"
#include "ArcherSkillKickShot.h"
#include "ArcherSkillFlippingArrow.h"
#include "ArcherSkillArrowShower.h"
#include "ArcherSkillPulseShot.h"
#include "ArcherSkillDiveShot.h"
#include "UI/SkillGaugeBar.h"

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
	Desperado->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_Desperado.M_Desperado"));

	PlayerController->SetQuickSlotSkill(Desperado, ESkillQuickSlot::SlotQ);
	//---------------------------------------------------------


	//KickShot Setting
	//---------------------------------------------------------
	UArcherSkillKickShot* KickShot = NewObject<UArcherSkillKickShot>();
	SkillArr.Push(KickShot);
	KickShot->SetAnimInstance(Anim);
	KickShot->SetMontage(Anim->GetKickShotMontage());
	KickShot->SetBaseClass(Archer);
	KickShot->SetQuickSlotKey(ESkillQuickSlot::SlotW);
	KickShot->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_KickShot.M_KickShot"));

	PlayerController->SetQuickSlotSkill(KickShot, ESkillQuickSlot::SlotW);
	//---------------------------------------------------------


	//FlippingArrow Setting
	//---------------------------------------------------------
	UArcherSkillFlippingArrow* FlippingArrow = NewObject<UArcherSkillFlippingArrow>();
	SkillArr.Push(FlippingArrow);
	FlippingArrow->SetAnimInstance(Anim);
	FlippingArrow->SetMontage(Anim->GetFlippingArrowMontage());
	FlippingArrow->SetBaseClass(Archer);
	FlippingArrow->SetQuickSlotKey(ESkillQuickSlot::SlotE);
	FlippingArrow->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_FlippingArrow.M_FlippingArrow"));

	PlayerController->SetQuickSlotSkill(FlippingArrow, ESkillQuickSlot::SlotE);
	//---------------------------------------------------------

	//ArrowShower Setting
	//---------------------------------------------------------
	UArcherSkillArrowShower* ArrowShower = NewObject<UArcherSkillArrowShower>();
	SkillArr.Push(ArrowShower);
	ArrowShower->SetAnimInstance(Anim);
	ArrowShower->SetMontage(Anim->GetArrowShowerMontage());
	ArrowShower->SetBaseClass(Archer);
	ArrowShower->SetQuickSlotKey(ESkillQuickSlot::SlotR);
	ArrowShower->SetSkillGaugeBar(PlayerController->GetSkillGaugeBar());
	ArrowShower->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_ArrowShower.M_ArrowShower"));

	PlayerController->SetQuickSlotSkill(ArrowShower, ESkillQuickSlot::SlotR);
	//---------------------------------------------------------

	//PulseShot Setting
	//---------------------------------------------------------
	UArcherSkillPulseShot* PulseShot = NewObject<UArcherSkillPulseShot>();
	SkillArr.Push(PulseShot);
	PulseShot->SetAnimInstance(Anim);
	PulseShot->SetMontage(Anim->GetPulseShotMontage());
	PulseShot->SetBaseClass(Archer);
	PulseShot->SetQuickSlotKey(ESkillQuickSlot::SlotF);
	PulseShot->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_PulseShot.M_PulseShot"));

	PlayerController->SetQuickSlotSkill(PulseShot, ESkillQuickSlot::SlotF);
	//---------------------------------------------------------

	//PulseShot Setting
	//---------------------------------------------------------
	UArcherSkillDiveShot* DiveShot = NewObject<UArcherSkillDiveShot>();
	SkillArr.Push(DiveShot);
	DiveShot->SetAnimInstance(Anim);
	DiveShot->SetMontage(Anim->GetDiveShotMontage());
	DiveShot->SetBaseClass(Archer);
	DiveShot->SetQuickSlotKey(ESkillQuickSlot::SlotD);
	DiveShot->SetMaterial(TEXT("/Game/GamePlay/Player/UI/Skill/M_DiveShot.M_DiveShot"));

	PlayerController->SetQuickSlotSkill(DiveShot, ESkillQuickSlot::SlotD);
	//---------------------------------------------------------
}