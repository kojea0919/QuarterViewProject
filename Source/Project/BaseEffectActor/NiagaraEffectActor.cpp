// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraEffectActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

void ANiagaraEffectActor::SpwanNiagaraEffect(const FTransform& Transform)
{
	//Spawn NiagaraComp
	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, Transform.GetLocation(),
		Transform.GetRotation().Rotator(), FVector(1.0f));

	RootComponent = NiagaraComp;

	NiagaraComp->OnSystemFinished.AddDynamic(this, &ANiagaraEffectActor::OnNiagaraSystemFinished);
}

void ANiagaraEffectActor::SpawnAndAttachNiagaraEffect(USkeletalMeshComponent* TargetMesh, FName SocketName)
{
	//Spawn NiagaraComp
	FTransform SocketTransform = TargetMesh->GetSocketTransform(SocketName);
	NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(NiagaraEffect, TargetMesh, SocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset,true);
	
	RootComponent = NiagaraComp;

	NiagaraComp->AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

	NiagaraComp->OnSystemFinished.AddDynamic(this, &ANiagaraEffectActor::OnNiagaraSystemFinished);

}

void ANiagaraEffectActor::SetEffectEnable(bool Enable)
{
	if (NiagaraComp)
	{
		NiagaraComp->SetVisibility(Enable);
	}
}

void ANiagaraEffectActor::OnNiagaraSystemFinished(UNiagaraComponent* PSystem)
{
	OnNiagaraSystemFinished_Impl();
}

