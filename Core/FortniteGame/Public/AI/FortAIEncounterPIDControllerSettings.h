#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"

struct FFortAIEncounterPIDControllerSettings {
public:
	DefineUnrealStruct(FFortAIEncounterPIDControllerSettings);

	DefineStructProperty(FCurveTableRowHandle, ProportionalGain);
	DefineStructProperty(FCurveTableRowHandle, IntegralGain);
	DefineStructProperty(FCurveTableRowHandle, DerivativeGain);
public:
	uint8 Padding[0x30];
};
