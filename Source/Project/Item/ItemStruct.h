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
	Max
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
	virtual FString GetItemStat() const { return FString(); };
	virtual ~FBaseItemInfoStruct() {};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;					//아이템 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;				//아이템 설명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Price;							//아이템 가격
};

USTRUCT(BlueprintType)
struct FWeaponItemInfoStruct : public FBaseItemInfoStruct
{
	GENERATED_USTRUCT_BODY()

public:

	virtual FString GetItemStat() const override
	{
		return FString(TEXT("공격력 : +")) + FString::FromInt(AttackStat) + FString(TEXT("  치명타 확률 : +")) + FString::FromInt(CriticalStat) + FString(TEXT("%"));
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int AttackStat;					//공격력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int CriticalStat;				//치명타 확률
};

USTRUCT(BlueprintType)
struct FArmorItemInfoStruct : public FBaseItemInfoStruct
{
	GENERATED_USTRUCT_BODY()


public:
	virtual FString GetItemStat() const override
	{
		return FString(TEXT("방어력 : +")) + FString::FromInt(ArmorStat);
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int ArmorStat;					//방어력
};

USTRUCT(BlueprintType)
struct FConsumptionItemInfoStruct : public FBaseItemInfoStruct
{
	GENERATED_USTRUCT_BODY()


public:
	virtual FString GetItemStat() const override
	{
		return FString(TEXT("체력 회복량 : +")) + FString::FromInt(HealAmount);
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int HealAmount;						//수치
};