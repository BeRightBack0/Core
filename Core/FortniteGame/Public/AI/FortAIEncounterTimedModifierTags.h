#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"

struct FFortAIEncounterTimedModifierTags {
public:
	DefineUnrealStruct(FFortAIEncounterTimedModifierTags);

	DefineStructProperty(float, TimeSeconds);
	DefineStructProperty(FGameplayTagContainer, GameplayTags);
public:
	uint8 Padding[0x28];
};
