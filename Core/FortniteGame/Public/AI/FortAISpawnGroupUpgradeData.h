#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

class UFortAISpawnGroupUpgrade;
class UFortAISpawnGroupUpgradeProbabilities;
class UFortAISpawnGroupCapsCategorySet;

struct FFortAISpawnGroupUpgradeData {
public:
	DefineUnrealStruct(FFortAISpawnGroupUpgradeData);

	DefineStructProperty(TSubclassOf<UFortAISpawnGroupUpgrade>, SpawnGroupUpgrade);
	DefineStructProperty(TSubclassOf<UFortAISpawnGroupUpgradeProbabilities>, UpgradeProbabilities);
	DefineStructProperty(TSubclassOf<UFortAISpawnGroupCapsCategorySet>, SpawnGroupCapsCategories);
	DefineStructProperty(FGameplayTagQuery, EncounterTagRequirementsQuery);
public:
	uint8 Padding[0x60];
};
