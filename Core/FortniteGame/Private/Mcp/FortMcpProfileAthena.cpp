#include "pch.h"
#include "FortniteGame/Public/Mcp/FortMcpProfileAthena.h"

#include "FortniteGame/Public/Mcp/McpProfileSys.h"

void UFortMcpProfileAthena::EndBattleRoyaleGame(
	const TArray<FFortQuestObjectiveCompletion>& Advance,
	uint8 MatchType,
	int32 MinutesAlive,
	int32 PersonalKills,
	int32 TeamKills,
	int32 Placement, 
	const TArray<FString>& Medals,
	FDedicatedServerUrlContext* Context
)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("EndBattleRoyaleGame");

	return Call(
		Func,
		Advance,
		MatchType,
		MinutesAlive,
		PersonalKills,
		TeamKills,
		Placement,
		Medals,
		Context
	);
}

void UFortMcpProfileAthena::EndBattleRoyaleGame(
	const TArray<FFortQuestObjectiveCompletion>& Advance,
	const FString& PlaylistId,
	const FAthenaMatchStats& MatchStats,
	int32 FriendshipXpBoost,
	int32 CosmeticXpBoost,
	float AntiAddictionPlayTimeMultiplier,
	bool ShouldAccumulateToProfileStats,
	bool ShouldSaveToRecentGameLists,
	const TArray<FString>& Medals,
	FDedicatedServerUrlContext* Context
)
{
	static UFunction* Func = nullptr;

	if (Func == nullptr)
		Func = FindFunction("EndBattleRoyaleGame");

	return Call(
		Func,
		Advance,
		PlaylistId,
		MatchStats,
		FriendshipXpBoost,
		CosmeticXpBoost,
		AntiAddictionPlayTimeMultiplier,
		ShouldAccumulateToProfileStats,
		ShouldSaveToRecentGameLists,
		Medals,
		Context
	);
}