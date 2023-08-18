// Simple Shooter Game.


#include "SSGameModeBase.h"

#include "Player/SSBaseCharacter.h"
#include "Player/SSPlayerController.h"
#include "UI/SSGameHUD.h"

ASSGameModeBase::ASSGameModeBase()
{
	DefaultPawnClass = ASSBaseCharacter::StaticClass();
	PlayerControllerClass = ASSPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
}
