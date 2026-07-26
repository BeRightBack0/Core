#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"

struct FFortPlayerPerformanceEstimateSettings {
public:
	DefineUnrealStruct(FFortPlayerPerformanceEstimateSettings);

	DefineStructProperty(FCurveTableRowHandle, PlayerPerformanceEstimateTransformMin);
	DefineStructProperty(FCurveTableRowHandle, PlayerPerformanceEstimateTransformOrigin);
	DefineStructProperty(FCurveTableRowHandle, PlayerPerformanceEstimateTransformMax);
	DefineStructProperty(float, EncounterPlayerPerformanceWeight);
	DefineStructProperty(float, PreviousWavePlayerPerformanceWeight);
	DefineStructProperty(float, CampaignPlayerPerformanceWeight);
public:
	uint8 Padding[0x40];
};
