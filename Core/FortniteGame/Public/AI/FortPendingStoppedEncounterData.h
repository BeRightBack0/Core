#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

#include "FortAIEncounterInfo.h"

struct FFortPendingStoppedEncounterData {
public:
	DefineUnrealStruct(FFortPendingStoppedEncounterData);

	DefineStructProperty(UFortAIEncounterInfo*, Encounter);
	DefineStructProperty(uint8, ObjectiveStatus);
	DefineStructProperty(bool, bForceDestroyAI);
	DefineStructProperty(bool, bEncounterCompletedSuccessfully);
public:
	uint8 Padding[0x10];
};
