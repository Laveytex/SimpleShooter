// Simple Shooter Game.


#include "Player/SSPlayerController.h"

#include "SSGameInstance.h"
#include "SSGameModeBase.h"
#include "Components/SSRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASSPlayerController::ASSPlayerController(): SSRespawnComponent(nullptr)
{
	SSRespawnComponent = CreateDefaultSubobject<USSRespawnComponent>("SSRespawnComponent");
}

void ASSPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OnNewPawn.Broadcast(InPawn);
}

void ASSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld())
	{
		const auto GameMod =  Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMod) return;
		GameMod->OnMatchStateChanged.AddUObject(this, &ASSPlayerController::OnMatchStateChange);
	}
}

void ASSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!InputComponent) return;
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASSPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASSPlayerController::OnMuteSound);
}

void ASSPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASSPlayerController::OnMatchStateChange(ESSMatchState State)
{
	if (State == ESSMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASSPlayerController::OnMuteSound()
{
	if (!GetWorld()) return;
	
	const auto SSGameInstance = GetWorld()->GetGameInstance<USSGameInstance>();
	if (!SSGameInstance) return;
	
	SSGameInstance->ToggleVolume();
}
