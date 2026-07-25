#pragma once
#include "pch.h"

#include <functional>
#include <vector>

// Some Fortnite getters (AFortAIDirector::GetCurrent, AFortAIGoalManager::GetCurrent, ...) are stripped
// to `return nullptr` in retail, so ICF folds them together with every other return-null function into a
// single shared stub. Two things follow from that:
//
//   - the getter has no address of its own, so it cannot be found and hooked directly, and
//   - every call to it is byte-identical to calls to the other folded functions, so callsites cannot be
//     identified by their shape either.
//
// The only sound way in is per-callsite: start from a function that is known to call the getter, and take
// the E8 whose target is the stub. That identifies the call exactly, with no byte signatures and no
// hand-counted offsets. This header holds the shared machinery; a caller supplies only the list of
// functions that contain the calls.
namespace StubCallsites {

	// ---- locating the function that contains the call ------------------------------------------

	// A string referenced from inside the function.
	inline uintptr_t FromString(const wchar_t* String)
	{
		auto Ref = Memcury::Scanner::FindStringRef(String, false);
		return Ref.IsValid() ? Ref.FindFunctionStart().Get() : 0;
	}

	// A reflected function: UFunction::Func is its exec thunk. Thunks come in two shapes.
	//
	// A thunk that unpacks parameters has a real prologue and unwind data, and reaches the
	// implementation with a call -- so hand it straight back and let FindCall locate the call by its
	// target. Don't try to pick the implementation out positionally: a thunk whose parameters are
	// FStrings or TArrays frees them *after* the call, so the last call is FMemory::Free, not the
	// implementation.
	//
	// A parameterless thunk is a 26-byte leaf: it fixes up FFrame::Code and tail-*jumps* to the
	// implementation. It has no unwind data to bound it and never calls anything, so follow the jmp.
	inline uintptr_t FromReflection(const char* FunctionPath)
	{
		auto Fn = (UFunction*)FUObjectArray::FindObject(FunctionPath);
		if (!Fn || !Fn->Func)
			return 0;

		uintptr_t Func = (uintptr_t)Fn->Func;

		if (Memcury::Scanner(Func).FindFunctionEnd().Get() > Func)
			return Func;

		for (int i = 0; i < 0x40; i++)
		{
			uintptr_t Cursor = Func + i;

			if (*(uint8*)Cursor == 0xE9)
				return Memcury::PE::Address(Cursor).RelativeOffset(1).Get();
		}

		return Func;
	}

	// A virtual, via a Finder VFT index and the class's default object.
	inline uintptr_t FromVTable(UClass* Class, uintptr_t Index)
	{
		if (!Class || !Index)
			return 0;

		return (uintptr_t)Class->GetDefaultObject()->VTable[Index];
	}

	// An RVA from Finder.
	inline uintptr_t FromOffset(uintptr_t Offset)
	{
		return Offset ? Offset + ImageBase : 0;
	}

	// A last resort for functions with no string, no reflection and no vtable entry: match the
	// function's prologue. Prefer the others -- a signature pins register and stack allocation, so it
	// only holds for the build it was taken from.
	inline uintptr_t FromSignature(const char* Signature)
	{
		return Memcury::Scanner::FindPattern(Signature, false).Get();
	}

	// A function located by one of its callees. Match the callee by signature, take the single branch
	// (E8 call or E9 tail-jmp) that targets it, and walk back to the function that makes it. Prefer this
	// to signing the caller's own prologue whenever the callee is reached from exactly one place: the
	// callee's body is a far more stable anchor across builds than the caller's register and stack
	// allocation, and a leaf helper often keeps the same shape where the caller's prologue drifts.
	//
	// The branch must include E9: the folded getter is frequently reached through a tail-call wrapper
	// that makes the stub call itself and then jmp-tails into the named body -- so the "caller" holding
	// the stub call is the wrapper, and its link to the body is a jmp, not a call. A call-only scan
	// misses it entirely.
	//
	// The exactly-one requirement is the point -- zero or several branch-refs make the caller ambiguous,
	// so this yields nothing and the next locator is tried rather than guessing which xref is wanted.
	inline uintptr_t FromXref(const char* CalleeSignature)
	{
		uintptr_t Callee = Memcury::Scanner::FindPattern(CalleeSignature, false).Get();
		if (!Callee)
			return 0;

		auto Refs = FindBranchRefsToAddress(Callee);
		if (Refs.size() != 1)
			return 0;

		return Memcury::Scanner(Refs[0]).FindFunctionStart().Get();
	}

	// ---- locating the call ---------------------------------------------------------------------

	// The return-null stub that Function calls. Anchor this on a function that calls the wanted getter
	// and nothing else that returns null, and it identifies the stub for every other site.
	inline uintptr_t ResolveStub(uintptr_t Function)
	{
		if (!Function)
			return 0;

		uintptr_t End = Memcury::Scanner(Function).FindFunctionEnd().Get();

		for (uintptr_t Cursor = Function; Cursor + 5 <= End; Cursor++)
		{
			if (*(uint8*)Cursor != 0xE8)
				continue;

			uintptr_t Target = Memcury::PE::Address(Cursor).RelativeOffset(1).Get();
			if (IsReturnNullStub(Target))
				return Target;
		}

		return 0;
	}

	// The call to Stub inside Function, or inside a function Function reaches within Depth levels of
	// direct calls. Callers routinely delegate rather than making the call themselves:
	// ABuildingActor::HandleDamaged notifies the director through a helper, and an exec thunk reaches
	// its implementation the same way (occasionally via one more hop, e.g. the
	// SetEncounterTopUtilityPercentages thunk goes through an intermediate before the real body).
	//
	// The call is always identified by its target, never by position, so the walk cannot pick the wrong
	// call -- the worst a too-shallow Depth can do is find nothing.
	inline uintptr_t FindCall(uintptr_t Function, uintptr_t Stub, int Depth = 2)
	{
		if (!Function || !Stub || Depth < 0)
			return 0;

		uintptr_t End = Memcury::Scanner(Function).FindFunctionEnd().Get();
		if (End <= Function)
			return 0;

		if (uintptr_t Addr = FindCallRefInRange(Function, End, Stub))
			return Addr;

		if (Depth == 0)
			return 0;

		for (uintptr_t Cursor = Function; Cursor + 5 <= End; Cursor++)
		{
			if (*(uint8*)Cursor != 0xE8)
				continue;

			uintptr_t Callee = Memcury::PE::Address(Cursor).RelativeOffset(1).Get();

			if (uintptr_t Addr = FindCall(Callee, Stub, Depth - 1))
				return Addr;
		}

		return 0;
	}

	// ---- locating a bound (lea'd) stub ---------------------------------------------------------

	// Everything above is for stubs that are *called*. A stripped void method that gets bound to a
	// delegate is different: the binder takes its address with `lea reg,[rip+rel32]` and stores it, so
	// there is no call to find and nothing to patch with PatchCallFar. The site is the lea, and it has
	// to be replaced with the address of a real implementation.
	//
	// The empty stub lea'd inside Function. Anchor this on a function known to bind the wanted method and
	// nothing else that was stripped to nothing.
	inline uintptr_t ResolveEmptyStub(uintptr_t Function)
	{
		if (!Function)
			return 0;

		uintptr_t End = Memcury::Scanner(Function).FindFunctionEnd().Get();

		for (uintptr_t Cursor = Function; Cursor + 7 <= End; Cursor++)
		{
			auto* b = reinterpret_cast<const uint8_t*>(Cursor);

			if ((b[0] != 0x48 && b[0] != 0x4C) || b[1] != 0x8D || (b[2] & 0xC7) != 0x05)
				continue;

			uintptr_t Target = Cursor + 7 + *reinterpret_cast<const int32_t*>(Cursor + 3);
			if (IsEmptyStub(Target))
				return Target;
		}

		return 0;
	}

	// True if the lea at Addr has its loaded value stored straight into an object field --
	// `mov [base+disp], reg` with the lea's own destination register and no SIB byte.
	//
	// This is what separates the binding we want from a decoy. A binder stores the method pointer into
	// the delegate it just allocated (`mov [rbx+10h], rax`), while unrelated uses of the same folded stub
	// spill it to a stack local (`mov [rsp+50h], rax`) -- and a stack store always encodes rm=100 (SIB),
	// so the two are trivially distinguishable without depending on the field offset. StartExitCraftSpawn
	// Timer contains both, and which one comes first changes between builds, so picking the first lea by
	// target alone silently patches the decoy on some builds.
	inline bool IsBoundIntoObject(uintptr_t Addr)
	{
		auto* b = reinterpret_cast<const uint8_t*>(Addr);

		int LeaReg = ((b[2] >> 3) & 7) + (b[0] == 0x4C ? 8 : 0);

		// The store usually follows immediately, but the compiler is free to interleave a few
		// instructions, so allow a short window.
		for (uintptr_t Cursor = Addr + 7; Cursor < Addr + 7 + 0x20; Cursor++)
		{
			auto* m = reinterpret_cast<const uint8_t*>(Cursor);

			if ((m[0] != 0x48 && m[0] != 0x4C) || m[1] != 0x89)
				continue;

			int Mod = (m[2] >> 6) & 3;
			int Reg = ((m[2] >> 3) & 7) + (m[0] == 0x4C ? 8 : 0);
			int Rm = m[2] & 7;

			if (Reg != LeaReg)
				continue;

			// mod 01/10 = [base+disp]; rm 100 = SIB, which is how rsp/stack stores encode
			if ((Mod == 1 || Mod == 2) && Rm != 4)
				return true;
		}

		return false;
	}

	// The lea that loads Stub inside Function, or inside a function Function reaches within Depth levels
	// of direct calls -- the load counterpart of FindCall, identified by target the same way. Where a
	// function loads the same folded stub more than once, the one bound into an object wins; only if none
	// qualifies does the first plain match stand in.
	inline uintptr_t FindLea(uintptr_t Function, uintptr_t Stub, int Depth = 2)
	{
		if (!Function || !Stub || Depth < 0)
			return 0;

		uintptr_t End = Memcury::Scanner(Function).FindFunctionEnd().Get();
		if (End <= Function)
			return 0;

		uintptr_t Fallback = 0;

		for (uintptr_t Cursor = Function; Cursor < End; )
		{
			uintptr_t Addr = FindLeaRefInRange(Cursor, End, Stub);
			if (!Addr)
				break;

			if (IsBoundIntoObject(Addr))
				return Addr;

			if (!Fallback)
				Fallback = Addr;

			Cursor = Addr + 1;
		}

		if (Fallback)
			return Fallback;

		if (Depth == 0)
			return 0;

		for (uintptr_t Cursor = Function; Cursor + 5 <= End; Cursor++)
		{
			if (*(uint8*)Cursor != 0xE8)
				continue;

			uintptr_t Callee = Memcury::PE::Address(Cursor).RelativeOffset(1).Get();

			if (uintptr_t Addr = FindLea(Callee, Stub, Depth - 1))
				return Addr;
		}

		return 0;
	}

	// ---- locators ------------------------------------------------------------------------------

	// A site may list several locators. They are tried in order and the first that actually yields the
	// call wins, so a site can carry a sturdy locator (reflection/string/vtable) ahead of the brittle
	// ones. This matters most for signatures: a signature pins register and stack allocation, so it only
	// holds for the build it was taken from, and a site can simply carry one per build.
	//
	// A locator that resolves to a function which turns out not to contain the call is not accepted --
	// the next locator is tried -- so a signature that happens to match the wrong function on some other
	// build degrades into "try the next one" rather than patching something random.
	using FLocator = std::function<uintptr_t()>;

	inline FLocator ByString(const wchar_t* String) { return [=] { return FromString(String); }; }
	inline FLocator ByReflection(const char* FunctionPath) { return [=] { return FromReflection(FunctionPath); }; }
	inline FLocator ByVTable(UClass* Class, uintptr_t Index) { return [=] { return FromVTable(Class, Index); }; }
	inline FLocator ByOffset(uintptr_t Offset) { return [=] { return FromOffset(Offset); }; }
	inline FLocator BySignature(const char* Signature) { return [=] { return FromSignature(Signature); }; }
	inline FLocator ByXref(const char* CalleeSignature) { return [=] { return FromXref(CalleeSignature); }; }

	// ---- patching ------------------------------------------------------------------------------

	struct FSite {
		const char* Name;
		std::vector<FLocator> Locators;
	};

	// Point every site's call at Detour. A site that doesn't resolve is logged by name and skipped, so
	// one missing anchor never takes the rest down with it.
	inline void Patch(const char* Label, uintptr_t Stub, void* Detour, std::initializer_list<FSite> Sites, bool bWarnIfNotFound = true)
	{
		for (const auto& Site : Sites)
		{
			uintptr_t Addr = 0;

			for (const auto& Locator : Site.Locators)
			{
				uintptr_t Function = Locator();
				if (!Function)
					continue;

				Addr = FindCall(Function, Stub);
				if (Addr)
					break;
			}

			if (!Addr) {
				if (bWarnIfNotFound) {
					Log(std::string("Failed to find patch for ") + Label + ": " + Site.Name);
				}
				continue;
			}

			Log(std::string(Label) + " Patch: " + Site.Name + " @ 0x" + std::format("{:X}", Addr - ImageBase));
			PatchCallFar(Addr, Detour);
		}
	}

	// Point every site's *bound-method load* at Detour, for methods stripped to an empty body and handed
	// to a delegate. Same locator/skip behaviour as Patch; the site's lea is repointed instead of a call,
	// so whatever the binder stores ends up being Detour and the delegate invokes it with the original
	// arguments (for a UObject method delegate, the bound object as the first argument).
	inline void PatchBound(const char* Label, uintptr_t Stub, void* Detour, std::initializer_list<FSite> Sites, bool bWarnIfNotFound = true)
	{
		for (const auto& Site : Sites)
		{
			uintptr_t Addr = 0;

			for (const auto& Locator : Site.Locators)
			{
				uintptr_t Function = Locator();
				if (!Function)
					continue;

				Addr = FindLea(Function, Stub);
				if (Addr)
					break;
			}

			if (!Addr) {
				if (bWarnIfNotFound) {
					Log(std::string("Failed to find patch for ") + Label + ": " + Site.Name);
				}
				continue;
			}

			Log(std::string(Label) + " Patch: " + Site.Name + " @ 0x" + std::format("{:X}", Addr - ImageBase));
			PatchLeaFar(Addr, Detour);
		}
	}
}
