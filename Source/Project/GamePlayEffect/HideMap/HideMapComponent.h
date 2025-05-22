#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HideMapComponent.generated.h"

UCLASS()
class PROJECT_API AHideMapComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	AHideMapComponent();

public:
	void SetOpacityMask(float Mask);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MapComponent;

	TArray<UMaterialInstanceDynamic*> DynMaterialArr;
};
