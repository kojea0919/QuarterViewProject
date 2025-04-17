// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SkillImageDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USkillImageDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetDragObject(class USkillQuickSlot* Object) { DragObject = Object; }
	class USkillQuickSlot* GetDragObject() const { return DragObject; }

private:
	class USkillQuickSlot* DragObject;
	
};
