#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FSlateBrush {
public:
	DefineUnrealStruct(FSlateBrush);
public:
	uint8 Padding[0x88];
};
