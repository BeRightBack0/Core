#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Core/Public/Misc/Guid.h"

struct FFortAISpawnerData {
public:
	DefineUnrealStruct(FFortAISpawnerData);

	DefineStructProperty(FGuid, SpawnGroupInstanceGuid);
public:
	uint8 Padding[0x60];
};
