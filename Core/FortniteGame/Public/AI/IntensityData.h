#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

class UBuildingEditModeMetadata;

struct FIntensityData {
public:
	DefineUnrealStruct(FIntensityData);

	DefineStructProperty(TArray<uint8>, ContributingFactors);
	DefineStructProperty(float, ContributionsTotal);
	DefineStructProperty(TArray<UBuildingEditModeMetadata*>, ExceptionEditModes);
	DefineStructProperty(float, ExceptionEditModeWeight);
public:
	uint8 Padding[0x30];
};
