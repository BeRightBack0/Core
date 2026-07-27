#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/Source/Runtime/CoreUObject/Public/UObject/ScriptDelegates.h"
#include "Engine/Source/Runtime/Core/Public/Misc/OutputDevice.h"

class AFortBluGloManager;
class AFortMission;

class AFortMissionManager : public AActor {
public:
	DefineUnrealClass(AFortMissionManager);

	DefineUProperty(AFortBluGloManager*, BluGloManager);
	DefineUProperty(TArray<AFortMission*>, Missions);
	DefineUProperty(AFortMission*, CurrentUIFocusedMission);
	DefineUProperty(AFortMission*, MissionClosestToPar);
	DefineUProperty(FMulticastScriptDelegate, OnMissionsUpdated);
	DefineUProperty(bool, bDisplaySecondaryMissionHeaders);
public:
	void OnRep_Missions();
};
