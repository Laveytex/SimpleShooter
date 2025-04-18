// Simple Shooter Game.


#include "SSGameModeBase.h"

#include "AIController.h"
#include "Player/SSBaseCharacter.h"
#include "Player/SSPlayerController.h"
#include "Player/SSPlayerState.h"
#include "UI/SSGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSSGameModBase, All, All);

ASSGameModeBase::ASSGameModeBase()
{
	DefaultPawnClass = ASSBaseCharacter::StaticClass();
	PlayerControllerClass = ASSPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
	PlayerStateClass = ASSPlayerState::StaticClass();
}

void ASSGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeamsInfo();

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

	if (--RoundCountDown == 0)
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

void ASSGameModeBase::ResetOnePlayers(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASSGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;

	int32 TeamID = 1;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<ASSPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		
		TeamID = TeamID == 1 ? 2 : 1;
	}
}

FLinearColor ASSGameModeBase::DetermineColorByTeamID(const int32 TeamID)
{
	if (TeamID - 1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID - 1];
	}
	return GameData.DefaultTeamColor;
}

void ASSGameModeBase::SetPlayerColor(const AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASSBaseCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto PlayerState = Cast<ASSPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	Character->SetPlayerColor(PlayerState->GetTeamColor());
}
