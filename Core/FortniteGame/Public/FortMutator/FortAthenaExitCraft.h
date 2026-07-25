#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/DataAsset.h"
#include "Engine/Source/Runtime/CoreUObject/Public/Templates/SubclassOf.h"

class AFortAthenaExitCraft;
class AFortAthenaExitCraftSpawner;

class UFortAthenaExitCraftInfo : public UPrimaryDataAsset {
public:
	DefineUnrealClass(UFortAthenaExitCraftInfo);

	DefineUProperty(TSubclassOf<AFortAthenaExitCraft>, ExitCaftClass);
	DefineUProperty(TSubclassOf<AFortAthenaExitCraftSpawner>, ExitCraftSpawnerClass);
};

class AFortAthenaExitCraft : public AActor {
public:
	DefineUnrealClass(AFortAthenaExitCraft);

	DefineUProperty(UFortAthenaExitCraftInfo*, ExitCraftInfo);
	DefineUProperty(uint8, CurrentState);
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
};
