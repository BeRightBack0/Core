#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/DataAsset.h"
#include "Engine/Source/Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "Engine/Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/ScalableFloat.h"

#include "FortniteGame/Public/FortEnums.h"

class AFortAthenaExitCraft;
class AFortAthenaExitCraftSpawner;

struct FExitCraftInfo {
public:
	DefineUnrealStruct(FExitCraftInfo);

	DefineStructProperty(FScalableFloat, ExitCraftSpawnerZOffset);
	DefineStructProperty(FScalableFloat, ExitCraftSpawnDelay);
	DefineStructProperty(FScalableFloat, ExitCraftZOffset);
	DefineStructProperty(FScalableFloat, ExitCraftTargetZOffset);
	DefineStructProperty(FScalableFloat, ExitCraftTimeToHoverLocation);
	DefineStructProperty(FScalableFloat, ExitCraftTimeToHoverRotation);
	DefineStructProperty(FScalableFloat, ExitZOffset);
	DefineStructProperty(FScalableFloat, ExitTime);
	DefineStructProperty(FScalableFloat, InteractionTime);
public:
	uint8 Padding[0x1E8];
};

class UFortAthenaExitCraftInfo : public UPrimaryDataAsset {
public:
	DefineUnrealClass(UFortAthenaExitCraftInfo);

	DefineUProperty(TSubclassOf<AFortAthenaExitCraft>, ExitCaftClass);
	DefineUProperty(TSubclassOf<AFortAthenaExitCraftSpawner>, ExitCraftSpawnerClass);
	DefineUProperty(FExitCraftInfo, ExitCraftInfo);
};

class AFortAthenaExitCraft : public AActor {
public:
	DefineUnrealClass(AFortAthenaExitCraft);

	DefineUProperty(UFortAthenaExitCraftInfo*, ExitCraftInfo);
	DefineUProperty(EExitCraftState, CurrentState);
public:
	void OnNewState(uint8 NewState) {
		static UFunction* Func = nullptr;

		if (Func == nullptr)
			Func = FindFunction("OnNewState");

		if (Func)
			Call(Func, NewState);
	}

	void OnRep_CurrentState() {
		static UFunction* Func = nullptr;

		if (Func == nullptr)
			Func = FindFunction("OnRep_CurrentState");

		if (Func)
			Call(Func);
	}

	void CheatDepart() {
		static UFunction* Func = nullptr;

		if (Func == nullptr)
			Func = FindFunction("CheatDepart");

		if (Func)
			Call(Func);
	}
};

class AFortAthenaExitCraftSpawner : public AActor {
public:
	DefineUnrealClass(AFortAthenaExitCraftSpawner);

	DefineUProperty(UFortAthenaExitCraftInfo*, ExitCraftInfo);
public:
	void StartExitCraftSpawnTimer() {
		static UFunction* Func = nullptr;

		if (Func == nullptr)
			Func = FindFunction("StartExitCraftSpawnTimer");

		if (Func)
			Call(Func);
	}

	void DestroyBlockingActors() {
		static UFunction* Func = nullptr;

		if (Func == nullptr)
			Func = FindFunction("DestroyBlockingActors");

		if (Func)
			Call(Func);
	}

	static void SpawnExitCraft(AFortAthenaExitCraftSpawner* This);

	static inline void (*BeginPlayOG)(AFortAthenaExitCraftSpawner* This);
	static void BeginPlay(AFortAthenaExitCraftSpawner* This);

	static void Hook();
};
