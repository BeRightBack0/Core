#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAIEncounterPawnDifficultyLevelModifier {
public:
	DefineUnrealStruct(FFortAIEncounterPawnDifficultyLevelModifier);

	DefineStructProperty(FGameplayTagQuery, EncounterTagRequirementsQuery);
	DefineStructProperty(FCurveTableRowHandle, DifficultyLevelModifierCurve);
public:
	uint8 Padding[0x58];
};
