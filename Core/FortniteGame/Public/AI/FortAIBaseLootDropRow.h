#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAIBaseLootDropRow {
public:
	DefineUnrealStruct(FFortAIBaseLootDropRow);

	DefineStructProperty(int32, Priority);
	DefineStructProperty(float, ItemDropChance);
	DefineStructProperty(FName, WorldItemLootTierGroup);
	DefineStructProperty(FName, WorldItemInstancedLootTierGroup);
	DefineStructProperty(FName, AccountItemLootTierGroup);
	DefineStructProperty(FGameplayTagContainer, AITagsContainer);
public:
	uint8 Padding[0x48];
};
