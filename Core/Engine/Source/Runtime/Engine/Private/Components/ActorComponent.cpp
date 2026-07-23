#include "pch.h"
#include "Engine/Source/Runtime/Engine/Classes/Components/ActorComponent.h"

#include "Engine/Source/Runtime/Engine/Classes/Engine/World.h"

void UActorComponent::SetIsReplicated(bool bShouldReplicate)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("SetIsReplicated");

	Call(Func, bShouldReplicate);
}

void UActorComponent::RegisterComponent()
{
	uintptr_t Offset = Finder::FindUActorComponent_RegisterComponentWithWorld();
	if (!Offset)
		return;

	UWorld* World = UWorld::GetWorld();
	if (!World)
		return;

	void (*RegisterComponentWithWorldInternal)(UActorComponent*, UWorld*) = decltype(RegisterComponentWithWorldInternal)(ImageBase + Offset);
	RegisterComponentWithWorldInternal(this, World);
}
