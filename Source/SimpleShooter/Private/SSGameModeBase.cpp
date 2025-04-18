// Simple Shooter Game.


#include "SSGameModeBase.h"

#include "AIController.h"
#include "Player/SSBaseCharacter.h"
#include "Player/SSPlayerController.h"
#include "UI/SSGameHUD.h"

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
