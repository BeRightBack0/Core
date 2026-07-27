#include "pch.h"
#include "FortniteGame/Public/BuildingActor/AthenaBigBaseWall.h"

void AAthenaBigBaseWall::OnRep_BarrierState()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_BarrierState");

	if (!Func) {
		Log("AAthenaBigBaseWall::OnRep_BarrierState: Failed to find function!");
		return;
	}

	return Call<void>(Func);
}

void AAthenaBigBaseWall::OnRep_ResetBool()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_ResetBool");

	if (!Func) {
		Log("AAthenaBigBaseWall::OnRep_ResetBool: Failed to find function!");
		return;
	}

	return Call<void>(Func);
}

void AAthenaBigBaseWall::OnRep_TimeUntilWallComesDown()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_TimeUntilWallComesDown");

	if (!Func) {
		Log("AAthenaBigBaseWall::OnRep_TimeUntilWallComesDown: Failed to find function!");
		return;
	}

	return Call<void>(Func);
}

void AAthenaBigBaseWall::OnRep_WallGravity()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_WallGravity");

	if (!Func) {
		Log("AAthenaBigBaseWall::OnRep_WallGravity: Failed to find function!");
		return;
	}

	return Call<void>(Func);
}
