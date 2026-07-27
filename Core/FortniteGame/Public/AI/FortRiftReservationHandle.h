#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/CoreUObject/Public/UObject/UnrealType.h"

struct FFortRiftReservationHandle {
public:
	DefineUnrealStruct(FFortRiftReservationHandle);

	DefineStructProperty(int32, RiftReservationID);
public:
	uint8 Padding[0x4];
};
