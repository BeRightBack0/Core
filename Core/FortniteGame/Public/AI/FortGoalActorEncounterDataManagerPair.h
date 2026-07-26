#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"

class AFortAIDirectorDataManager;

struct FFortGoalActorEncounterDataManagerPair {
public:
	DefineUnrealStruct(FFortGoalActorEncounterDataManagerPair);

	DefineStructProperty(AActor*, GoalActor);
	DefineStructProperty(AFortAIDirectorDataManager*, EncounterDataManager);
public:
	uint8 Padding[0x10];
};
