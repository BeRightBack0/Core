#pragma once
#include "pch.h"

#include "NetDriver.h"

class Error;
class FNetworkNotify;
class UDemoNetDriver;
class UDemoNetConnection;
class FRepState;

class UDemoNetDriver : public UNetDriver {
public:
	DefineUnrealClass(UDemoNetDriver);

	DefineUProperty(float, CheckpointSaveMaxMSPerFrame);
	DefineUProperty(bool, bIsLocalReplay);
public:
	static void Hook() {
		Log("Hooked UDemoNetDriver!");
	}
};