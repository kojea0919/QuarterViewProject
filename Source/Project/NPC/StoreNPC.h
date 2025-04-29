// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StoreNPC.generated.h"

UCLASS()
class PROJECT_API AStoreNPC : public ACharacter
{
	GENERATED_BODY()

	friend class UStore;

public:
	AStoreNPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

	//void SetupStoreUI();		//Store UI에 NPC가 가지고 있는 Item Arr 정보를 넘기는 함수

	const class UBaseItem* GetItem(const FString& ItemName);

private:
	void InitWeaponItemList();
	void InitArmorItemList();
	void InitPotionItemList();


private:
	UPROPERTY(EditAnywhere, Category = ItemList, meta = (AllowPrivateAccess = "true"))
	TMap<FString,class UWeaponItem*> WeaponItemMap;

	UPROPERTY(EditAnywhere, Category = ItemList, meta = (AllowPrivateAccess = "true"))
	TMap<FString, class UArmorItem*> ArmorItemMap;

	UPROPERTY(EditAnywhere, Category = ItemList, meta = (AllowPrivateAccess = "true"))
	TMap<FString, class UPotionItem*> PotionItemMap;

	class AArcherPlayerController* ArcherController;
};
