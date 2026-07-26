#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Core/Public/Misc/Guid.h"

class UFortAISpawnGroup;

struct FSpawnGroupInstanceInfo {
public:
	DefineUnrealStruct(FSpawnGroupInstanceInfo);

	DefineStructProperty(UFortAISpawnGroup*, SpawnGroup);
	DefineStructProperty(int32, NumActiveAlive);
	DefineStructProperty(int32, TotalGroupCost);
	DefineStructProperty(int32, SpawnPointsUsed);
	DefineStructProperty(int32, NumEngaged);
	DefineStructProperty(bool, bReadyToSpawn);
	DefineStructProperty(bool, bFinishedSpawning);
	DefineStructProperty(FGuid, GroupGuid);
	DefineStructProperty(int32, EnemySpawnDataIndex);
	DefineStructProperty(float, TimeSelected);
	DefineStructProperty(int32, NextEnemyToSpawnIndex);
public:
	uint8 Padding[0x140];
};
