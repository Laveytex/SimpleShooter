// Simple Shooter Game.


#include "Player/SSPlayerController.h"
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

void ASSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!InputComponent) return;
	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASSPlayerController::OnPauseGame);
}

void ASSPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}
