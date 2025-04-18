// Simple Shooter Game.


#include "SSGameModeBase.h"

#include "AIController.h"
#include "Player/SSBaseCharacter.h"
#include "Player/SSPlayerController.h"
#include "UI/SSGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSSGameModBase, All, All);

ASSGameModeBase::ASSGameModeBase()
{
	DefaultPawnClass = ASSBaseCharacter::StaticClass();
	PlayerControllerClass = ASSPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}

void ASSGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();

	CurrentRound = 1;
	StartGameRound();
}

UClass* ASSGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASSGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto SSAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(SSAIController);
	}
}

void ASSGameModeBase::StartGameRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer
	(GameRoundTimerHandle, this, &ASSGameModeBase::GameTimerUpdate, 1.f, true);
}

void ASSGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogSSGameModBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum)

	/*const auto TimeRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
	RoundCountDown -= TimeRate;*/

	if (--RoundCountDown == 0 )
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartGameRound();
		}
		else
		{
			UE_LOG(LogSSGameModBase, Display, TEXT("=========GAME OVER========="))
		}
	}
}

void ASSGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayers(It->Get());
	}
}

void ASSGameModeBase::ResetOnePlayers(AController* InController)
{
	if (InController && InController->GetPawn())
	{
		InController->GetPawn()->Reset();
	}
	
	RestartPlayer(InController);
}
