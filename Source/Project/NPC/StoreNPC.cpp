// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/StoreNPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "Archer/Archer.h"
#include "Archer/ArcherPlayerController.h"
#include "Item/WeaponItem.h"
#include "Item/ArmorItem.h"
#include "Item/PotionItem.h"
#include "Item/BaseItem.h"

AStoreNPC::AStoreNPC()
	: ArcherController(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AStoreNPC::BeginPlay()
{
	Super::BeginPlay();
	
	InitWeaponItemList();
	InitArmorItemList();
	InitPotionItemList();
}

void AStoreNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStoreNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AStoreNPC::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AArcher * Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		//Archer
		Archer->SetVisibleInteractionUI(true);

		AArcherPlayerController * PlayerController = Archer->GetController<AArcherPlayerController>();
		if (PlayerController)
		{
		
			PlayerController->SetupStoreUI(this,Archer);
		}
	}
}

void AStoreNPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	AArcher* Archer = Cast<AArcher>(OtherActor);
	if (Archer)
	{
		Archer->SetVisibleInteractionUI(false);

		ArcherController = nullptr;

		AArcherPlayerController* PlayerController = Archer->GetController<AArcherPlayerController>();
		if (PlayerController)
		{
			PlayerController->SetVisibilityIntersectionKey(false);

			PlayerController->SetupStoreUI(nullptr,nullptr);
		}
	}
}

const UBaseItem* AStoreNPC::GetItem(const FString& ItemName)
{
	UWeaponItem ** WeapopnItem = WeaponItemMap.Find(ItemName);

	if (WeapopnItem)
		return *WeapopnItem;

	UArmorItem** ArmorItem = ArmorItemMap.Find(ItemName);
	if (ArmorItem)
		return *ArmorItem;

	UPotionItem** PotionItem = PotionItemMap.Find(ItemName);
	if (PotionItem)
		return *PotionItem;

	return nullptr;
}

void AStoreNPC::InitWeaponItemList()
{
	UWeaponItem* NewItem = NewObject<UWeaponItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(TEXT("초보자 활"), TEXT("기본적인 활. 특별한 기능은 없다."),100, 10, 0);

		UTexture2D * ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Weapon/Texture/BasicBow.BasicBow"));
		if(ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		WeaponItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UWeaponItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("강화된 활")), FString(TEXT("초보자용보다 더 튼튼하고 쓸만하다.")), 200, 40, 0);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Weapon/Texture/RareBow.RareBow"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		WeaponItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UWeaponItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("숙련자의 활")), FString(TEXT("내구성과 정확도가 향상되어 더 높은 성능을 자랑하며, 크리티컬 확률이 증가한다.")), 400, 100, 10);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Weapon/Texture/EpicBow.EpicBow"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		WeaponItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UWeaponItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("명장의 활")), FString(TEXT("크리티컬 확률이 크게 상승하고, 전투에서 강력한 성능을 발휘한다.")), 800, 200, 40);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Weapon/Texture/LegendaryBow.LegendaryBow"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		WeaponItemMap.Add(NewItem->GetItemName(), NewItem);
	}
}

void AStoreNPC::InitArmorItemList()
{
	UArmorItem* NewItem = NewObject<UArmorItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(TEXT("갑옷"), TEXT("갑옷"), 300, 10, EArmorType::Chest);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Armor/Texture/T_Chest.T_Chest"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		ArmorItemMap.Add(NewItem->GetItemName(),NewItem);
	}

	NewItem = NewObject<UArmorItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("장갑")), FString(TEXT("장갑")), 200, 10, EArmorType::Glove);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Armor/Texture/T_Glove.T_Glove"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		ArmorItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UArmorItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("모자")), FString(TEXT("모자")), 200, 100, EArmorType::Hat);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Armor/Texture/T_Hat.T_Hat"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		ArmorItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UArmorItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("바지")), FString(TEXT("바지")), 300, 100, EArmorType::Pants);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Armor/Texture/T_Pants.T_Pants"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		ArmorItemMap.Add(NewItem->GetItemName(), NewItem);
	}
}

void AStoreNPC::InitPotionItemList()
{
	UPotionItem* NewItem = NewObject<UPotionItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(TEXT("고급 물약"), TEXT("고급 물약"), 20, 300);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Potion/Texture/HPPotion1.HPPotion1"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		PotionItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UPotionItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("달인 물약")), FString(TEXT("달인 물약")), 40, 500);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Potion/Texture/HPPotion2.HPPotion2"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		PotionItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UPotionItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("강화 물약")), FString(TEXT("강화 물약")), 60, 700);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Potion/Texture/HPPotion3.HPPotion3"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		PotionItemMap.Add(NewItem->GetItemName(), NewItem);
	}

	NewItem = NewObject<UPotionItem>();
	if (NewItem->IsValidLowLevel())
	{
		NewItem->SetItemInfo(FString(TEXT("정화 물약")), FString(TEXT("정화 물약")), 80, 900);

		UTexture2D* ItemTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Item/Potion/Texture/HPPotion4.HPPotion4"));
		if (ItemTexture->IsValidLowLevel())
			NewItem->SetTexture(ItemTexture);
		PotionItemMap.Add(NewItem->GetItemName(), NewItem);
	}
}

