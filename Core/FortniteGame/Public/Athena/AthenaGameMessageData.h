#pragma once
#include "pch.h"

#include "Engine/Source/Runtime/Core/Public/Internationalization/Text.h"

class USoundCue;

struct FAthenaGameMessageData {
public:
	DefineUnrealStruct(FAthenaGameMessageData);

	DefineStructProperty(uint8, MsgType);
	DefineStructProperty(FText, MsgText);
	DefineStructProperty(USoundCue*, MsgSound);
	DefineStructProperty(float, MsgDelay);
	DefineStructProperty(bool, bIsTeamBased);
	DefineStructProperty(int32, TeamIndex);
public:
	uint8 Padding[0x38];
};
