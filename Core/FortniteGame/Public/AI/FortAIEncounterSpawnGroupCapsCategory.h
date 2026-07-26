#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAIEncounterSpawnGroupCapsCategory {
public:
	DefineUnrealStruct(FFortAIEncounterSpawnGroupCapsCategory);

	DefineStructProperty(FGameplayTagQuery, TagQuery);
	DefineStructProperty(bool, bApplyGroupPopulationCurveToCategoryMax);
	DefineStructProperty(FCurveTableRowHandle, InitialSpawnGroupAvailabilityDelaySeconds);
	DefineStructProperty(FCurveTableRowHandle, SpawnGroupAvailabilityDelaySeconds);
	DefineStructProperty(FGameplayTagQuery, UnlockingTagQuery);
	DefineStructProperty(TArray<uint8>, SpawnGroupCapsPerPlayerCount);
	DefineStructProperty(float, InitialSpawnGroupAvailabilityTime);
	DefineStructProperty(float, NumActiveCategorySpawnGroups);
	DefineStructProperty(TArray<float>, SpawnGroupAvailabilityTimes);
	DefineStructProperty(int32, NumSpawnGroupAvailable);
public:
	uint8 Padding[0x140];
};
