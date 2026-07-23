#include "pch.h"
#include "FortniteGame/Public/BuildingActor/BuildingFoundation.h"

void ABuildingFoundation::OnRep_ServerStreamedInLevel()
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("OnRep_ServerStreamedInLevel");

	if (!Func) {
		return;
	}

	Call(Func);
}

bool ABuildingFoundation::SelectAndSetupMyBuildingLevel(void* ReservedRandomValues)
{
	uintptr_t Addr = Finder::FindABuildingFoundation_SelectAndSetupMyBuildingLevel();
	if (!Addr) {
		return false;
	}

	bool (*SelectAndSetupMyBuildingLevelInternal)(ABuildingFoundation*, void*) = decltype(SelectAndSetupMyBuildingLevelInternal)(ImageBase + Addr);
	return SelectAndSetupMyBuildingLevelInternal(this, ReservedRandomValues);
}

void ABuildingFoundation::SetDynamicFoundationEnabled(bool bEnabled)
{
	static UFunction* Func = nullptr;
	static bool bSearched = false;

	if (!bSearched) {
		bSearched = true;
		Func = FindFunction("SetDynamicFoundationEnabled");
	}

	if (!Func) {
		return;
	}

	Call(Func, bEnabled);
}

void ABuildingFoundation::Show()
{
	SetDynamicFoundationEnabled(true);

	bServerStreamedInLevel = true;
	OnRep_ServerStreamedInLevel();

	if (LevelToStream != "None") {
		return;
	}

	SelectAndSetupMyBuildingLevel();
}

void ABuildingFoundation::SetupFoundations()
{
	std::vector<const char*> FoundationPaths;

	if (Version::Fortnite_Version >= 6 && Version::Fortnite_Version < 7)
	{
		FoundationPaths.push_back(Version::Fortnite_Version <= 6.10
			? "/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations.PersistentLevel.LF_Athena_StreamingTest12"
			: (Version::Fortnite_Version <= 6.21
				? "/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations.PersistentLevel.LF_Lake1"
				: "/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations.PersistentLevel.LF_Lake2"));

		FoundationPaths.push_back(Version::Fortnite_Version <= 6.10
			? "/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations.PersistentLevel.LF_Athena_StreamingTest13"
			: "/Game/Athena/Maps/Athena_POI_Foundations.Athena_POI_Foundations.PersistentLevel.LF_FloatingIsland");
	}

	for (const char* Path : FoundationPaths)
	{
		ABuildingFoundation* Foundation = StaticLoadObject<ABuildingFoundation>(Path);
		if (!Foundation) {
			Log("ABuildingFoundation::SetupFoundations: not found " + std::string(Path));
			continue;
		}

		Foundation->Show();

		Log("Enabled foundation " + Foundation->GetName().ToString());
	}

	SetupIslandScripting();
}

void ABuildingFoundation::DumpFoundations()
{
	for (UObject* Object : FUObjectArray::FindObjects("LF_"))
	{
		ABuildingFoundation* Foundation = ::Cast<ABuildingFoundation>(Object);
		if (!Foundation) {
			continue;
		}

		std::string Worlds;
		if (Foundation->_HasAdditionalWorlds()) {
			for (auto& World : Foundation->AdditionalWorlds) {
				std::string Path = World.ObjectID.AssetPathName.ToString().ToString();
				if (Path != "None") {
					Worlds += " " + Path;
				}
			}
		}

		Log("Foundation " + Object->GetName().ToString()
			+ " LevelToStream=" + (Foundation->_HasLevelToStream() ? Foundation->LevelToStream.ToString().ToString() : "<none>")
			+ " AdditionalWorlds=" + (Worlds.empty() ? "<none>" : Worlds));
	}
}

void ABuildingFoundation::SetupIslandScripting()
{
	UClass* IslandScriptingClass = (UClass*)FUObjectArray::FindObjectFast("BP_IslandScripting_C");
	if (!IslandScriptingClass) {
		return;
	}

	UProperty* UpdateMap = IslandScriptingClass->FindPropertyByName("UpdateMap");
	UProperty* CachedTimeProp = IslandScriptingClass->FindPropertyByName("CachedTime");
	UProperty* IslandPositionProp = IslandScriptingClass->FindPropertyByName("IslandPosition");

	for (UObject* IslandScripting : FUObjectArray::GetObjectsOfClass(IslandScriptingClass))
	{
		if (!IslandScripting || IslandScripting == IslandScriptingClass->GetDefaultObject()) {
			continue;
		}

		if (UpdateMap) {
			*(bool*)((uintptr_t)IslandScripting + UpdateMap->Offset_Internal) = true;

			if (UFunction* OnRep = IslandScripting->FindFunction("OnRep_UpdateMap")) {
				IslandScripting->Call(OnRep);
			}
		}
		else if (CachedTimeProp) {
			if (UFunction* OnRep = IslandScripting->FindFunction("OnRep_CachedTime")) {
				IslandScripting->Call(OnRep);
			}

			if (UFunction* OnRep = IslandScripting->FindFunction("OnRep_IslandPosition")) {
				IslandScripting->Call(OnRep);
			}
		}
	}
}
