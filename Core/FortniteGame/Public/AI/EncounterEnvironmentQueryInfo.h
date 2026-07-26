#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

class UEnvQuery;

struct FEncounterEnvironmentQueryInfo {
public:
	DefineUnrealStruct(FEncounterEnvironmentQueryInfo);

	DefineStructProperty(UEnvQuery*, EnvironmentQuery);
	DefineStructProperty(TArray<uint8>, QueryParams);
	DefineStructProperty(bool, bIsDirectional);
public:
	uint8 Padding[0x28];
};
