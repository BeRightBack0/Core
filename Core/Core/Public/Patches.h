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

		uintptr_t PrevVivoxInit = 0;
		for (int RefNum = 0; RefNum < 2; RefNum++) {
			auto InitRef = Memcury::Scanner::FindStringRef(L"FVivox::Initialize failure: %s (%i)", false, RefNum);
			uintptr_t VivoxInitPatch = InitRef.IsValid() ? InitRef.FindFunctionStart().Get() : 0;

			if (VivoxInitPatch && VivoxInitPatch != PrevVivoxInit) {
				PrevVivoxInit = VivoxInitPatch;
				MH_CreateHook(LPVOID(VivoxInitPatch), RetNullptr, 0);
				Log("Patched: " + std::to_string(VivoxInitPatch - ImageBase) + " with RetNullptr");
			}
		}

		auto ConnectRef = Memcury::Scanner::FindStringRef(L"Connect failed: %s (%i)", false);
		uintptr_t VivoxConnectPatch = ConnectRef.IsValid() ? ConnectRef.FindFunctionStart().Get() : 0;
		if (VivoxConnectPatch) {
			MH_CreateHook(LPVOID(VivoxConnectPatch), RetNullptr, 0);
			Log("Patched: " + std::to_string(VivoxConnectPatch - ImageBase) + " with RetNullptr");
		}
	}
};