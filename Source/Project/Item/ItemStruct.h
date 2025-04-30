// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.generated.h"

//현재 아이템 타입
//------------------------------
enum class EItemListType
{
	Weapon = 0,
	Armor,
	Potion,
	None
};
//------------------------------

//현재 방어구 아이템 타입
//------------------------------
enum class EArmorType
{
	Hat = 0,
	Chest,
	Pants,
	Glove,
	None
};
//------------------------------

/**
 * 
 */
class PROJECT_API ItemStruct
{
public:
	ItemStruct();
	~ItemStruct();
};

USTRUCT(BlueprintType)
struct FBaseItemInfoStruct
{
	GENERATED_USTRUCT_BODY()

public:
	FBaseItemInfoStruct()
		: Price(0), AttackStat(0), CriticalStat(0),
		ArmorStat(0), HealAmount(0)
	{
		ItemName = TEXT("");
		Description = TEXT("");
	}

public:
	FString GetWeaponItemStat() const
	{
		return FString(TEXT("공격력 : +")) + FString::FromInt(AttackStat) + FString(TEXT("  치명타 확률 : +")) + FString::FromInt(CriticalStat) + FString(TEXT("%"));	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	}	
	FString GetArmorItemStat() const
	{
		return FString(TEXT("방어력 : +")) + FString::FromInt(ArmorStat);
	}
	FString GetPotionItemStat() const
	{
		return FString(TEXT("체력 회복량 : +")) + FString::FromInt(HealAmount);
	}

public:
	FString ItemName;					//아이템 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;				//아이템 설명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Price;							//아이템 가격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int AttackStat;					//공격력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int CriticalStat;				//치명타 확률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int ArmorStat;					//방어력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int HealAmount;						//수치

	EItemListType ItemType;
};

//USTRUCT(BlueprintType)
//struct FWeaponItemInfoStruct : public FBaseItemInfoStruct
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	FWeaponItemInfoStruct()
//		: AttackStat(0), CriticalStat(0)
//	{}
//
//public:
//	virtual FString GetItemStat() const override
//	{
//		return FString(TEXT("공격력 : +")) + FString::FromInt(AttackStat) + FString(TEXT("  치명타 확률 : +")) + FString::FromInt(CriticalStat) + FString(TEXT("%"));
//	}
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int AttackStat;					//공격력
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int CriticalStat;				//치명타 확률
//};
//
//USTRUCT(BlueprintType)
//struct FArmorItemInfoStruct : public FBaseItemInfoStruct
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	FArmorItemInfoStruct()
//		: ArmorStat(0)
//	{}
//
//public:
//	virtual FString GetItemStat() const override
//	{
//		return FString(TEXT("방어력 : +")) + FString::FromInt(ArmorStat);
//	}
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int ArmorStat;					//방어력
//};
//
//USTRUCT(BlueprintType)
//struct FConsumptionItemInfoStruct : public FBaseItemInfoStruct
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	FConsumptionItemInfoStruct()
//		: HealAmount(0)
//	{}
//
//public:
//	virtual FString GetItemStat() const override
//	{
//		return FString(TEXT("체력 회복량 : +")) + FString::FromInt(HealAmount);
//	}
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int HealAmount;						//수치
//};