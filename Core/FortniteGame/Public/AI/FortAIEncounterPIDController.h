#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FFortAIEncounterPIDController {
public:
	DefineUnrealStruct(FFortAIEncounterPIDController);

	DefineStructProperty(float, ProportionalGain);
	DefineStructProperty(float, IntegralGain);
	DefineStructProperty(float, DerivativeGain);
public:
	uint8 Padding[0x68];
};
