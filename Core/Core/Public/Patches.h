#pragma once
#include "pch.h"

#include "Version.h"

class Patches {
public:
	static void ApplyPatches() {
		uintptr_t WidgetCrashPatch = Memcury::Scanner::FindStringRef(L"Unable to create the widget {0}, no outer provided.").FindFunctionStart().Get();
		if (WidgetCrashPatch) {
			MH_CreateHook(LPVOID(WidgetCrashPatch), RetNullptr, 0);
			Log("Patched: " + std::to_string(WidgetCrashPatch - ImageBase) + " with RetNullptr");
		}
	}
};