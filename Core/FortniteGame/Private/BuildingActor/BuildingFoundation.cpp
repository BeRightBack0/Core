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
		ABuildingFoundation* Foundation = (ABuildingFoundation*)FUObjectArray::FindObject(Path);
		if (!Foundation) {
			Log("ABuildingFoundation::SetupFoundations: not found " + std::string(Path));
			continue;
		}

		Foundation->Show();
		Log("Enabled foundation " + Foundation->GetName().ToString());
	}
}
