#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FFortAIEncounterWaveProgressEstimation {
public:
	DefineUnrealStruct(FFortAIEncounterWaveProgressEstimation);

	DefineStructProperty(float, SectionProgressEstimate);
	DefineStructProperty(float, SectionStartTime);
	DefineStructProperty(float, LastWaveProgressUpdateTime);
	DefineStructProperty(float, PeakAndFadeWavePercentage);
	DefineStructProperty(float, MaxAdjustmentPerSecond);
	DefineStructProperty(uint8, CurrentSection);
	DefineStructProperty(int32, NumberOfWaveSegments);
public:
	uint8 Padding[0x1C];
};
