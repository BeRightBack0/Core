#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FUtilityTypeFloatPair {
public:
	DefineUnrealStruct(FUtilityTypeFloatPair);

	DefineStructProperty(uint8, Utility);
	DefineStructProperty(float, Value);
public:
	uint8 Padding[0x8];
};
