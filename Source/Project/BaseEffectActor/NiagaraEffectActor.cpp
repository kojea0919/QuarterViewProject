// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraEffectActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "WorldSubSystem/EffectObjectPool.h"

ANiagaraEffectActor::ANiagaraEffectActor()
	: EffectEnable(true)
{

}

void ANiagaraEffectActor::SpwanNiagaraEffect(const FTransform& Transform)
{
	//Spawn NiagaraComp
	if (nullptr == NiagaraComp)
	{
		NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, Transform.GetLocation(),
			Transform.GetRotation().Rotator(), FVector(1.0f),false);

		RootComponent = NiagaraComp;

		NiagaraComp->OnSystemFinished.AddDynamic(this, &ANiagaraEffectActor::OnNiagaraSystemFinished);
	}
	else
	{
		NiagaraComp->SetWorldLocationAndRotation(Transform.GetLocation(), Transform.GetRotation().Rotator());
	}
}

void ANiagaraEffectActor::SpawnAndAttachNiagaraEffect(USkeletalMeshComponent* TargetMesh, FName SocketName)
{
	//Spawn NiagaraComp
	if (nullptr == NiagaraComp)
	{
		FTransform SocketTransform = TargetMesh->GetSocketTransform(SocketName);
		NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraEffect, TargetMesh, SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);

		RootComponent = NiagaraComp;

		NiagaraComp->AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

		NiagaraComp->OnSystemFinished.AddDynamic(this, &ANiagaraEffectActor::OnNiagaraSystemFinished);
	}
	else
	{
		NiagaraComp->AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}

void ANiagaraEffectActor::SetEffectEnable(bool Enable)
{
	SetActorHiddenInGame(!Enable);
	
	if (!NiagaraComp)
		return;

	EffectEnable = Enable;
	if (Enable)
	{
		NiagaraComp->ResetSystem();
		NiagaraComp->Activate(true);
	}
	else
	{
		NiagaraComp->Deactivate();
		NiagaraComp->DeactivateImmediate();
	}
}

void ANiagaraEffectActor::OnNiagaraSystemFinished(UNiagaraComponent* PSystem)
{
	if (!EffectEnable)
		return;

	OnNiagaraSystemFinished_Impl();
}

