#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/CurveTable.h"

struct FFortEncounterPawnNumberCaps {
public:
	DefineUnrealStruct(FFortEncounterPawnNumberCaps);

	DefineStructProperty(bool, bApplyPawnNumberCaps);
	DefineStructProperty(TArray<FCurveTableRowHandle>, PawnCapsPerPlayerCount);
public:
	uint8 Padding[0x18];
};
