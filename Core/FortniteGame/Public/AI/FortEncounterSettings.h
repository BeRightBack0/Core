#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"

class UEnvQuery;
class UFortDifficultyOptionCategoryEncounter;

struct FFortEncounterSettings {
public:
	DefineUnrealStruct(FFortEncounterSettings);

	DefineStructProperty(TArray<uint8>, ForbiddenSpawnDirections);
	DefineStructProperty(bool, bRiftsDestroyPlayerBuiltBuildings);
	DefineStructProperty(bool, bMustFindSpawnPoints);
	DefineStructProperty(bool, bTrackCombatParticipation);
	DefineStructProperty(bool, bDisplayThreatVisuals);
	DefineStructProperty(int32, NumRiftsToUseOverride);
	DefineStructProperty(bool, bUseEQSQueryToFindAISpawnLocations);
	DefineStructProperty(bool, bRelevantForTotalAICap);
	DefineStructProperty(float, PreSpawnRequeryTime);
	DefineStructProperty(UEnvQuery*, RiftSelectionQuery);
	DefineStructProperty(TArray<AActor*>, ScriptedSpawnPoints);
	DefineStructProperty(TArray<AActor*>, WorkingScriptedSpawnPoints);
	DefineStructProperty(TArray<UFortDifficultyOptionCategoryEncounter*>, InjectedOverrideCategories);
public:
	uint8 Padding[0x58];
};
