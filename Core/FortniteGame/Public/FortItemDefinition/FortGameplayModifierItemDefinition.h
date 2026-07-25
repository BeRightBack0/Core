#pragma once
#include "pch.h"

#include "FortItemDefinition.h"

class UFortGameplayModifierItemDefinition : public UFortAccountItemDefinition {
public:
	DefineUnrealClass(UFortGameplayModifierItemDefinition);

	DefineUProperty(TArray<TSoftClassPtr<UClass>>, Mutators);
};
