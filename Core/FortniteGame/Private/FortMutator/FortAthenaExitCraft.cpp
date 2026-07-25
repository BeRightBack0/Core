#include "pch.h"
#include "FortniteGame/Public/FortMutator/FortAthenaExitCraft.h"

#include "Core/Public/StubCallsites.h"

#include "FortniteGame/Public/FortMutator/FortAthenaMutator_Heist.h"
#include "FortniteGame/Public/FortGameState/FortGameStateAthena.h"

void AFortAthenaExitCraftSpawner::SpawnExitCraft(AFortAthenaExitCraftSpawner* This)
{
	if (!This)
		return;

	UWorld* World = UWorld::GetWorld();
	if (!World)
		return;

	UFortAthenaExitCraftInfo* Info = This->ExitCraftInfo;
	if (!Info) {
		Log("AFortAthenaExitCraftSpawner::SpawnExitCraft: spawner has no ExitCraftInfo!");
		return;
	}

	UClass* CraftClass = Info->ExitCaftClass.Get();
	if (!CraftClass) {
		Log("AFortAthenaExitCraftSpawner::SpawnExitCraft: ExitCaftClass is null on " + Info->GetName().ToString());
		return;
	}

	FVector SpawnLoc = This->K2_GetActorLocation();
	FRotator SpawnRot = This->K2_GetActorRotation();

	float ZOffset = 0.0f;
	float TargetZOffset = 0.0f;

	if (Info->_HasExitCraftInfo()) {
		ZOffset = Info->ExitCraftInfo.ExitCraftZOffset.Evaluate(0);
		TargetZOffset = Info->ExitCraftInfo.ExitCraftTargetZOffset.Evaluate(0);
	}

	SpawnLoc.Z += ZOffset;

	AFortAthenaExitCraft* Craft = (AFortAthenaExitCraft*)World->SpawnActor(CraftClass, SpawnLoc, SpawnRot);
	if (!Craft) {
		Log("AFortAthenaExitCraftSpawner::SpawnExitCraft: failed to spawn " + CraftClass->GetName().ToString());
		return;
	}

	if (!Craft->ExitCraftInfo)
		Craft->ExitCraftInfo = Info;

	Craft->CurrentState = EExitCraftState::GetSpawned();
	Craft->OnNewState(EExitCraftState::GetSpawned());
	Craft->OnRep_CurrentState();
	Craft->ForceNetUpdate();

	AFortGameStateAthena* GameState = World->GameState ? World->GameState->Cast<AFortGameStateAthena>() : nullptr;
	if (GameState) {
		for (AFortAthenaMutator* Mutator : GameState->GameplayMutators) {
			AFortAthenaMutator_Heist* Heist = Mutator ? Mutator->Cast<AFortAthenaMutator_Heist>() : nullptr;
			if (!Heist)
				continue;

			for (int32 i = 0; i < Heist->SpawnedExitCraftList.Num(); i++) {
				FHeistExitCraftData& Entry = Heist->SpawnedExitCraftList.GetWithSize(i, FHeistExitCraftData::GetSize());

				if (Entry.ExitCraftSpawner == This && !Entry.SpawnedExitCraft) {
					Entry.SpawnedExitCraft = Craft;
					break;
				}
			}

			// tell the mutator about the new exitcraft we spawned
			Heist->OnExitCraftSpawned(Craft, This);
		}
	}

	Log("AFortAthenaExitCraftSpawner::SpawnExitCraft: spawned " + Craft->GetName().ToString()
		+ " at " + This->GetName().ToString()
		+ " ZOffset=" + std::to_string((int32)ZOffset)
		+ " hover=" + std::to_string((int32)TargetZOffset)
		+ " state=" + std::to_string((int32)Craft->CurrentState));
}

void AFortAthenaExitCraftSpawner::BeginPlay(AFortAthenaExitCraftSpawner* This)
{
	BeginPlayOG(This);

	if (!This)
		return;

	This->StartExitCraftSpawnTimer();

	Log("AFortAthenaExitCraftSpawner::BeginPlay: started spawn timer on " + This->GetName().ToString());
}

void AFortAthenaExitCraftSpawner::Hook()
{
	if (Finder::FindAActor_BeginPlayVFT()) {
		HookEveryVTableIdx(
			AFortAthenaExitCraftSpawner::StaticClass(),
			Finder::FindAActor_BeginPlayVFT(),
			BeginPlay,
			(LPVOID*)&BeginPlayOG
		);
	}

	uintptr_t Binder = StubCallsites::FromReflection("Function /Script/FortniteGame.FortAthenaExitCraftSpawner.StartExitCraftSpawnTimer");
	uintptr_t Stub = StubCallsites::ResolveEmptyStub(Binder);

	StubCallsites::PatchBound("AFortAthenaExitCraftSpawner::SpawnExitCraft", Stub, SpawnExitCraft, {
		{ "AFortAthenaExitCraftSpawner::StartExitCraftSpawnTimer", {
			[=] { return Binder; } } },
		});
}
