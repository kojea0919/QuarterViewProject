// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterimageEffect.h"
#include "Components/PoseableMeshComponent.h"
#include "Project/WorldSubSystem/EffectObjectPool.h"

AAfterimageEffect::AAfterimageEffect()
	: DynMaterial(nullptr), Opacity(1.0f), OpacitySpeed(2.0f)
{
	//Component Init
	Mesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("Mesh"));

	//Component Setting
	//----------------------------------------
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("/Game/Player/Archer/Mesh/Player.Player"));
	if (SK_MESH.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_MESH.Object);
	}
	//----------------------------------------
}

void AAfterimageEffect::CopyAnimationPos(USkeletalMeshComponent* MasterComponent)
{
	APawn* Master = GetOwner<APawn>();
	if (Master)
	{
		TArray<FTransform> BoneTransforms;
		for (int32 BoneIndex = 0; BoneIndex < MasterComponent->GetNumBones(); ++BoneIndex)
		{
			BoneTransforms.Add(MasterComponent->GetBoneTransform(BoneIndex));
		}

		// Mesh에 본 트랜스폼 설정하기
		for (int32 BoneIndex = 0; BoneIndex < BoneTransforms.Num(); ++BoneIndex)
		{
			Mesh->SetBoneTransformByName(MasterComponent->GetBoneName(BoneIndex), BoneTransforms[BoneIndex], EBoneSpaces::WorldSpace);
		}
	}
}

void AAfterimageEffect::SetOpacity(float NewOpacity)
{
	Opacity = NewOpacity;
	DynMaterial->SetScalarParameterValue(FName("Opacity"), Opacity);
}

void AAfterimageEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Opacity Update
	//--------------------------------------------
	Opacity -= DeltaTime * OpacitySpeed;

	//전부 투명해지면 ObjectPool에 Return
	if (Opacity <= 0.0f)
	{
		SetActorTickEnabled(false);

		if (EffectObjPool)
			EffectObjPool->ReturnAfterimageEffect(this);
	}
	DynMaterial->SetScalarParameterValue(FName("Opacity"), Opacity);

	//--------------------------------------------
}

void AAfterimageEffect::LoadMaterial()
{
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Player/Gunner/Mesh/Material/M_Afterimage.M_Afterimage"));
	DynMaterial = UMaterialInstanceDynamic::Create(Material, Mesh);
	Mesh->SetMaterial(0, DynMaterial);
	Mesh->SetMaterial(1, DynMaterial);

	DynMaterial->SetScalarParameterValue(FName("Opacity"), Opacity);
}
