#pragma once

#include "EngineMinimal.h"

UENUM(BlueprintType, meta = (ScriptName = "ESkillQuickSlotEnum"))
enum class ESkillQuickSlot :uint8
{
	SlotQ = 0,
	SlotW,
	SlotE,
	SlotV,
	SlotMax
};