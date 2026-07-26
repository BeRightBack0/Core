#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FAIEncounterSpawnGroupWeights {
public:
	DefineUnrealStruct(FAIEncounterSpawnGroupWeights);
public:
	uint8 Padding[0x18];
};
