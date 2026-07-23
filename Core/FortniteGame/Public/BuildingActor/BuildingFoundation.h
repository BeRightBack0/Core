#pragma once
#include "pch.h"

#include "BuildingSMActor.h"

#include "Engine/Source/Runtime/Engine/Classes/Engine/LevelStreaming.h"

class ABuildingFoundation : public ABuildingSMActor {
public:
	DefineUnrealClass(ABuildingFoundation);

	DefineBitfieldUProperty(bConditionalFoundation);
	DefineBitfieldUProperty(bServerStreamedInLevel);

	DefineUProperty(FName, LevelToStream);
	DefineUProperty(ULevelStreaming*, LevelStreamInfo);
	DefineUProperty(TArray<TSoftObjectPtr<UWorld>>, AdditionalWorlds);

	void OnRep_ServerStreamedInLevel();
	void SetDynamicFoundationEnabled(bool bEnabled);

	bool SelectAndSetupMyBuildingLevel(void* ReservedRandomValues = nullptr);

	void Show();

	static void SetupFoundations();
	static void SetupIslandScripting();

	static void DumpFoundations();
};
