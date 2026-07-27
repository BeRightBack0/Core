#include "pch.h"
#include "FortniteGame/Public/FortMutator/FortAthenaMutator_Barrier.h"

void AFortAthenaMutator_Barrier::CheckHealthThreshold(uint8 TeamNum)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("CheckHealthThreshold");

	if (!Func) {
		Log("AFortAthenaMutator_Barrier::CheckHealthThreshold: Failed to find function!");
		return;
	}

	return Call<void>(Func, TeamNum);
}

void AFortAthenaMutator_Barrier::OnGamePhaseStepChanged(uint8 GamePhaseStep)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnGamePhaseStepChanged");

	if (!Func) {
		Log("AFortAthenaMutator_Barrier::OnGamePhaseStepChanged: Failed to find function!");
		return;
	}

	return Call<void>(Func, GamePhaseStep);
}

void AFortAthenaMutator_Barrier::OnMutatorGameplayEvent(int32 EventId, int32 EventParam1, int32 EventParam2, int32 EventParam3)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnMutatorGameplayEvent");

	if (!Func) {
		Log("AFortAthenaMutator_Barrier::OnMutatorGameplayEvent: Failed to find function!");
		return;
	}

	return Call<void>(Func, EventId, EventParam1, EventParam2, EventParam3);
}
