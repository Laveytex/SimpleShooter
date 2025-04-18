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
	void SetPlayerColor(const AController* Controller);
};
