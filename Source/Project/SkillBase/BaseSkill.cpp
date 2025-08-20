// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkill.h"
#include "Archer/Archer.h"
#include "Archer/Animation/ArcherAnimInstance.h"
#include "UI/SkillQuickSlot.h"
#include "DrawDebugHelpers.h"
#include "DamageType/ArcherBasicDamageType.h"
#include "Monster/Boss.h"

UBaseSkill::UBaseSkill()
	: Archer(nullptr), AnimInstance(nullptr), SkillUIMaterial(nullptr), SkillType(ESkillType::Base), CurSlot(nullptr),
	IsPlacedSkill(false), NeedRotation(false), CurCollisionIdx(0), SkillMontage(nullptr),
	CoolTime(1.0f), ElapsedSkillTime(0), IsCoolDown(false)
{
}

bool UBaseSkill::Use()
{
	if (nullptr == Archer)
		return false;

	//다른 스킬 중에는 공격 불가능
	if (Archer->GetMoveSkillOn() || Archer->GetUseSkill())
	{
		return false;
	}

	if (!AnimInstance->Montage_IsPlaying(SkillMontage))
	{
		if (CurSlot)
			CurSlot->PlayUseSkillAnimation();

		Archer->SetUseSkill(true);

		if (NeedRotation)
			Archer->RotateMouseDirectionTimeLineVersion();

		AnimInstance->Montage_Play(SkillMontage);

		//AnimInstnace의 BindSkillMontageEndDelegate함수를 호출해서
		//Animation이 끝나면 Skill의 End함수를 호출하도록 한다.
		AnimInstance->BindSkillMontageEndDelegate(SkillMontage);
		AnimInstance->SetCurSkill(this);

		if(SkillType == ESkillType::Base)
			StartCoolDown();

		return true;
	}

	return false;
}

void UBaseSkill::End()
{
	if (Archer)
		Archer->SetMoveAble(true);
}

void UBaseSkill::ResumeMontage()
{
	if (SkillMontage)
		AnimInstance->Montage_Resume(SkillMontage);
}

void UBaseSkill::StopMontage()
{
	if (SkillMontage)
		AnimInstance->Montage_Stop(0.2f, SkillMontage);
}

void UBaseSkill::PlaySkillMontageSection(int32 NewSection)
{
	if (SkillMontage)
	{
		AnimInstance->PlayComboSkillMontageSection(NewSection);
	}
}

bool UBaseSkill::IsPlayingMontage()
{
	if (SkillMontage)
		return AnimInstance->Montage_IsPlaying(SkillMontage);
	return false;
}

void UBaseSkill::UpdateCoolDownEffect(float DeltaTime)
{
	//경과 시간 업데이트
	//---------------------------------------------
	ElapsedSkillTime += DeltaTime;

	float CurPercent = ElapsedSkillTime / CoolTime;
	//---------------------------------------------

	CurPercent = FMath::Clamp(CurPercent, 0.0f, 1.0f);

	SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), CurPercent);
}

void UBaseSkill::SetMaterial(const TCHAR* FileName)
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, FileName);
	
	if (Material)
	{
		SkillUIMaterial = UMaterialInstanceDynamic::Create(Material, this);

		SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), 0.0f);
	}
}

void UBaseSkill::SetQuickSlot(USkillQuickSlot* Slot)
{
	if (Slot->IsValidLowLevel())
		CurSlot = Slot;
}

void UBaseSkill::MultiHitSkillProc()
{
	CheckEnemyOverlap();

	UWorld* World = nullptr;
	if (nullptr != Archer)
		World = Archer->GetWorld();

	if (nullptr == World)
		return;

	++CallDamageTimerNum;
	if (CallDamageTimerNum == MaxCallDamageTimerNum)
	{
		CallDamageTimerNum = 0;

		World->GetTimerManager().ClearTimer(DamageTimer);
	}
}

void UBaseSkill::StartCoolDown()
{
	//쿨다운이 적용 중이지 않은 경우에만 실행
	if (!IsCoolDown)
	{
		Archer->GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this,
			&UBaseSkill::EndCoolDown, CoolTime, false);
		IsCoolDown = true;
		ElapsedSkillTime = 0.0f;

		CurSlot->SetRemainCoolTimeVisible(true);
	}
}

void UBaseSkill::EndCoolDown()
{
	IsCoolDown = false;
	ElapsedSkillTime = 0.0f;

	SkillUIMaterial->SetScalarParameterValue(FName("CoolDownPercent"), 0.0f);

	CurSlot->SetRemainCoolTimeVisible(false);
	CurSlot->PlaySkillCoolTimeEndAnimation();
}

void UBaseSkill::CheckEnemyOverlap()
{
	if (nullptr == Archer || nullptr == Archer->GetWorld())
		return;

	TArray<FHitResult> HitResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Archer);

	FVector CollisionSpawnLocation;
	if (!IsPlacedSkill)
	{
		CollisionSpawnLocation = Archer->GetActorLocation() + Archer->GetActorForwardVector() * CollisionForwardScaleArr[CurCollisionIdx] +
			FVector(0.0f, 0.0f, CollisionHeightOffsetArr[CurCollisionIdx]);	
	}
	else
	{
		CollisionSpawnLocation = CollisionLocation;
	}


	FCollisionShape CollisionShape;
	switch (CollisionTypeArr[CurCollisionIdx])
	{
	case ECollisionType::Box:
		CollisionShape = FCollisionShape::MakeBox(CollisionExtentArr[CurCollisionIdx]);
		break;
	case ECollisionType::Capsule:
		CollisionShape = FCollisionShape::MakeCapsule(CollisionExtentArr[CurCollisionIdx]);
		break;
	case ECollisionType::Sphere:
		CollisionShape = FCollisionShape::MakeSphere(CollisionExtentArr[CurCollisionIdx].X);
		break;
	default:
		return;
	}

	bool IsHit = Archer->GetWorld()->SweepMultiByObjectType(HitResults, CollisionSpawnLocation, CollisionSpawnLocation,
		Archer->GetActorQuat(), ObjectQueryParams, CollisionShape, Params);

	//충돌이 된 경우
	if (IsHit)
	{
		for (auto& Hit : HitResults)
		{
			if (Cast<ABoss>(Hit.GetActor()))
			{
				UGameplayStatics::ApplyDamage(
					Hit.GetActor(),
					SkillDamage + FMath::RandRange(-SkillDamage / 10.f, SkillDamage / 10.0f),
					Archer->GetInstigatorController(),
					Archer,
					UArcherBasicDamageType::StaticClass());
			}
		}
	}

	/*switch (CollisionTypeArr[CurCollisionIdx])
	{
	case ECollisionType::Box:
		DrawDebugBox(Archer->GetWorld(),
			CollisionSpawnLocation,
			CollisionExtentArr[CurCollisionIdx],
			Archer->GetActorQuat(),
			FColor::Green, false, 2);
		break;
	case ECollisionType::Capsule:
		CollisionShape = FCollisionShape::MakeCapsule(CollisionExtentArr[CurCollisionIdx]);
		break;
	case ECollisionType::Sphere:
		DrawDebugSphere(Archer->GetWorld(),
			CollisionSpawnLocation,
			CollisionExtentArr[CurCollisionIdx].X, 12,
			FColor::Green, false,2.0f);
		break;
	default:
		return;
	}*/
}

void UBaseSkill::StartMutliHitSkillEnemyOverlap()
{
	UWorld* World = nullptr;
	if (nullptr != Archer)
		World = Archer->GetWorld();

	if (nullptr != World)
	{
		//충돌 처리를 위한 Timer 설정
		//----------------------------------------------------------------------------------------
		World->GetTimerManager().SetTimer(DamageTimer, this, &UBaseSkill::MultiHitSkillProc, DamageTermTime, true);
		//----------------------------------------------------------------------------------------
	}
}


