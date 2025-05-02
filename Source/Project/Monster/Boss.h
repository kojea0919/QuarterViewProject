
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss.generated.h"

UCLASS()
class PROJECT_API ABoss : public ACharacter
{
	GENERATED_BODY()

public:
	ABoss();

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	void BasicTypeDamageProc();

	FVector GetRandomVector();

private:
	//Damage관련 변수
	//-----------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageText> DamageTextWidgetClass;

	const FVector DamageTextOffset = { 0.0f,-125.0f,60.0f };
	
	const float RandomVectorRange= 30;
	//-----------------------------------------------------------------------------

};
