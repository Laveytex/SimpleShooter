// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SSGameModeBase.generated.h"

class AAIController;

UCLASS()
class SIMPLESHOOTER_API ASSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASSGameModeBase();
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	static void Killed(const AController* KillerController, const AController* VictimActor);

	FGameData GetGameDate() const { return GameData; }
	int32 GetCurrentRoundNum() const { return CurrentRound; }
	int32 GetRoundSecondsRemaining() const { return RoundCountDown; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	int32 CurrentRound = 1;
	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimerHandle;
	
	void SpawnBots();
	void StartGameRound();
	void GameTimerUpdate();

	void ResetPlayers();
	void ResetOnePlayers(AController* Controller);

	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID);
	static void SetPlayerColor(const AController* Controller);

	void LogPlayerInfo() const;
};
