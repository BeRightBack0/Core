#pragma once
#include "pch.h"

#include "BuildingSMActor.h"

class ABuildingFoundation : public ABuildingSMActor {
public:
	DefineUnrealClass(ABuildingFoundation);

	DefineBitfieldUProperty(bConditionalFoundation);
	DefineBitfieldUProperty(bServerStreamedInLevel);

	void OnRep_ServerStreamedInLevel();
	void SetDynamicFoundationEnabled(bool bEnabled);

	void Show();

	static void SetupFoundations();
};
