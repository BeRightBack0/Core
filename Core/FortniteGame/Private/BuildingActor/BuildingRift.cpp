#include "pch.h"
#include "FortniteGame/Public/BuildingActor/BuildingRift.h"

#include "FortniteGame/Public/AI/FortAIPawn.h"

void ABuildingRift::BroadcastRiftSpawningAI()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("BroadcastRiftSpawningAI");

	if (!Func) {
		Log("ABuildingRift::BroadcastRiftSpawningAI: Failed to find function!");
		return;
	}

	return const_cast<ABuildingRift*>(this)->Call<void>(Func);
}

void ABuildingRift::OnRep_CosmeticState()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_CosmeticState");

	if (!Func) {
		Log("ABuildingRift::OnRep_CosmeticState: Failed to find function!");
		return;
	}

	return const_cast<ABuildingRift*>(this)->Call<void>(Func);
}

void ABuildingRift::OnRep_RiftIsActive()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_RiftIsActive");

	if (!Func) {
		Log("ABuildingRift::OnRep_RiftIsActive: Failed to find function!");
		return;
	}

	return const_cast<ABuildingRift*>(this)->Call<void>(Func);
}

void ABuildingRift::OnRep_RiftIsVisible()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_RiftIsVisible");

	if (!Func) {
		Log("ABuildingRift::OnRep_RiftIsVisible: Failed to find function!");
		return;
	}

	return const_cast<ABuildingRift*>(this)->Call<void>(Func);
}

void ABuildingRift::OnPlaced()
{
}

void ABuildingRift::OnActivated()
{
}

void ABuildingRift::OnDeactivated()
{
}

void ABuildingRift::OnRemoved()
{
}

void ABuildingRift::OnSpawnAI()
{
}

void ABuildingRift::OnStartedEncounterSpawn(AFortAIPawn* SpawnedAI)
{
}

void ABuildingRift::OnFinishedEncounterSpawn(AFortAIPawn* SpawnedAI)
{
}

void ABuildingRift::execOnPlaced(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	Stack.IncrementCode();

	if (Context)
		Context->OnPlaced();

	if (execOnPlacedOG)
		execOnPlacedOG(Context, Stack, Result);
}

void ABuildingRift::execOnActivated(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	Stack.IncrementCode();

	if (Context)
		Context->OnActivated();

	if (execOnActivatedOG)
		execOnActivatedOG(Context, Stack, Result);
}

void ABuildingRift::execOnDeactivated(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	Stack.IncrementCode();

	if (Context)
		Context->OnDeactivated();

	if (execOnDeactivatedOG)
		execOnDeactivatedOG(Context, Stack, Result);
}

void ABuildingRift::execOnRemoved(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	Stack.IncrementCode();

	if (Context)
		Context->OnRemoved();

	if (execOnRemovedOG)
		execOnRemovedOG(Context, Stack, Result);
}

void ABuildingRift::execOnSpawnAI(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	Stack.IncrementCode();

	if (Context)
		Context->OnSpawnAI();

	if (execOnSpawnAIOG)
		execOnSpawnAIOG(Context, Stack, Result);
}

void ABuildingRift::execOnStartedEncounterSpawn(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	AFortAIPawn* SpawnedAI = nullptr;
	Stack.StepCompiledIn(&SpawnedAI);
	Stack.IncrementCode();

	if (Context)
		Context->OnStartedEncounterSpawn(SpawnedAI);

	if (execOnStartedEncounterSpawnOG)
		execOnStartedEncounterSpawnOG(Context, Stack, Result);
}

void ABuildingRift::execOnFinishedEncounterSpawn(ABuildingRift* Context, FFrame& Stack, void* Result)
{
	AFortAIPawn* SpawnedAI = nullptr;
	Stack.StepCompiledIn(&SpawnedAI);
	Stack.IncrementCode();

	if (Context)
		Context->OnFinishedEncounterSpawn(SpawnedAI);

	if (execOnFinishedEncounterSpawnOG)
		execOnFinishedEncounterSpawnOG(Context, Stack, Result);
}

void ABuildingRift::Hook()
{
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnPlaced", execOnPlaced, execOnPlacedOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnActivated", execOnActivated, execOnActivatedOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnDeactivated", execOnDeactivated, execOnDeactivatedOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnRemoved", execOnRemoved, execOnRemovedOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnSpawnAI", execOnSpawnAI, execOnSpawnAIOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnStartedEncounterSpawn", execOnStartedEncounterSpawn, execOnStartedEncounterSpawnOG);
	ExecHook("Function /Script/FortniteGame.BuildingRift.OnFinishedEncounterSpawn", execOnFinishedEncounterSpawn, execOnFinishedEncounterSpawnOG);

	Log("Hooked ABuildingRift");
}
