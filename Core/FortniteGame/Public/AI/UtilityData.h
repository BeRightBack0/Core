#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Core/Public/Math/Color.h"

struct FUtilityData {
public:
	DefineUnrealStruct(FUtilityData);

	DefineStructProperty(TArray<uint8>, ContributingFactors);
	DefineStructProperty(float, ContributionsTotal);
	DefineStructProperty(bool, bApplyRecentSelectionPenalty);
	DefineStructProperty(float, RecentlySelectedPenaltyPercentage);
	DefineStructProperty(float, PenaltyFallOffRate);
	DefineStructProperty(FString, DebugGraphName);
	DefineStructProperty(FLinearColor, DebugGraphColor);
public:
	uint8 Padding[0x40];
};
