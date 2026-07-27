#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FFortAIEncounterQueryDirectionTracker {
public:
	DefineUnrealStruct(FFortAIEncounterQueryDirectionTracker);

	DefineStructProperty(bool, bHasTriedPreviousDirections);
	DefineStructProperty(TArray<uint8>, PreviousQueryDirections);
	DefineStructProperty(TArray<uint8>, ChosenDirections);
	DefineStructProperty(TArray<uint8>, FailedDirections);
	DefineStructProperty(TArray<uint8>, AvailableDirections);
public:
	uint8 Padding[0x48];
};
