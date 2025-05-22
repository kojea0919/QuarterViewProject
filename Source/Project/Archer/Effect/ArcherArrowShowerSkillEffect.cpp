// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherArrowShowerSkillEffect.h"
#include "NiagaraSystem.h"
#include "WorldSubSystem/EffectObjectPool.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"

AArcherArrowShowerSkillEffect::AArcherArrowShowerSkillEffect()
{
	NiagaraEffect = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/GamePlay/Player/Archer/Effect/Niagara/NS_Archer_ArrowShower.NS_Archer_ArrowShower"));

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("SKILLSOUND"));
	AudioComp->bAutoActivate = false;

	static ConstructorHelpers::FObjectFinder<USoundWave> SW_SOUND(TEXT("/Game/GamePlay/Player/Archer/Sound/SW_ArrowShower.SW_ArrowShower"));
	if (SW_SOUND.Succeeded())
		SoundWave = SW_SOUND.Object;
}

void AArcherArrowShowerSkillEffect::OnNiagaraSystemFinished_Impl()
{
	EffectObjPool->ReturnArcherArrowShowerSkillEffect(this);
}

void AArcherArrowShowerSkillEffect::SpwanNiagaraEffect(const FTransform& Transform)
{
	Super::SpwanNiagaraEffect(Transform);

	UGameplayStatics::PlaySoundAtLocation(this, SoundWave, GetActorLocation() - FVector(0.0f, 0.0f, 100));
}

void AArcherArrowShowerSkillEffect::BeginPlay()
{
	Super::BeginPlay();

	AudioComp->SetSound(SoundWave);
}
