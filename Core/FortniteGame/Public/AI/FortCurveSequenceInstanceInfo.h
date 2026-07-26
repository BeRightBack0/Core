#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FFortCurveSequenceInstanceInfo {
public:
	DefineUnrealStruct(FFortCurveSequenceInstanceInfo);

	DefineStructProperty(float, CurrentCurveSequenceTime);
public:
	uint8 Padding[0x8];
};
