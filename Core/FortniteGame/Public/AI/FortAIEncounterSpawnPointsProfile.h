#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAIEncounterSpawnPointsProfile {
public:
	DefineUnrealStruct(FFortAIEncounterSpawnPointsProfile);

	DefineStructProperty(FGameplayTagContainer, EncounterTypeTags);
	DefineStructProperty(TArray<FCurveTableRowHandle>, MaxSpawnPointsPerPlayerCount);
	DefineStructProperty(TArray<FCurveTableRowHandle>, MinSpawnPointsPerPlayerCount);
public:
	uint8 Padding[0x40];
};
