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

		uintptr_t VivoxConnectPatch = Memcury::Scanner::FindStringRef(L"FVivox::Connect").FindFunctionStart().Get();
		if (VivoxConnectPatch) {
			MH_CreateHook(LPVOID(VivoxConnectPatch), RetNullptr, 0);
			Log("Patched: " + std::to_string(VivoxConnectPatch - ImageBase) + " with RetNullptr");
		}
	}
};