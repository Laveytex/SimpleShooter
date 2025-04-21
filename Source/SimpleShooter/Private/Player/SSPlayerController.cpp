// Simple Shooter Game.


#include "Player/SSPlayerController.h"
#include "Components/SSRespawnComponent.h"

ASSPlayerController::ASSPlayerController(): SSRespawnComponent(nullptr)
{
	SSRespawnComponent = CreateDefaultSubobject<USSRespawnComponent>("SSRespawnComponent");
}
