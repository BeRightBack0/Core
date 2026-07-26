#include "pch.h"
#include "FortniteGame/Public/AI/FortAIEncounterInfo.h"

void UFortAIEncounterInfo::NotifyNightStarted() {
	if (bOnlyActiveAtNight)
		bCanBeActive = true;
}