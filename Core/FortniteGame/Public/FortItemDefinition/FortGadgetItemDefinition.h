#pragma once
#include "pch.h"

#include "FortWorldItemDefinition.h"

class UFortAbilitySet;
class UCustomCharacterPart;

class UFortGadgetItemDefinition : public UFortWorldItemDefinition {
public:
	DefineUnrealClass(UFortGadgetItemDefinition);

	DefineBitfieldUProperty(bDropAllOnEquip);
	DefineUProperty(TSoftObjectPtr<UFortAbilitySet>, AbilitySet);
	DefineUProperty(TArray<UCustomCharacterPart*>, CharacterParts);
	DefineUProperty(TSoftClassPtr<UClass>, GameplayAbility);
};

class UAthenaGadgetItemDefinition : public UFortGadgetItemDefinition {
public:
	DefineUnrealClass(UAthenaGadgetItemDefinition);
};