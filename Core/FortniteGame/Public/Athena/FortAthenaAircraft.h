#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/Engine/Classes/GameFramework/Actor.h"

class AFortAthenaAircraft : public AActor {
public:
	DefineUnrealClass(AFortAthenaAircraft);

	DefineUProperty(float, FlightStartTime);
	DefineUProperty(float, FlightEndTime);
	DefineUProperty(float, DropStartTime);
	DefineUProperty(float, DropEndTime);
};