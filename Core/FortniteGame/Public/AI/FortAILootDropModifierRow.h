#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAILootDropModifierRow {
public:
	DefineUnrealStruct(FFortAILootDropModifierRow);

	DefineStructProperty(int32, Priority);
	DefineStructProperty(float, ItemDropChanceMultiplier);
	DefineStructProperty(FGameplayTagContainer, AITagsContainer);
public:
	uint8 Padding[0x30];
};
