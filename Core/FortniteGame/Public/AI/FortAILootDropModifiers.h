#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"
#include "Engine/Source/Runtime/Engine/Classes/Engine/DataTable.h"

struct FFortAILootDropModifiers {
public:
	DefineUnrealStruct(FFortAILootDropModifiers);

	DefineStructProperty(TArray<FDataTableRowHandle>, LootDropModifierRows);
public:
	uint8 Padding[0x60];
};
