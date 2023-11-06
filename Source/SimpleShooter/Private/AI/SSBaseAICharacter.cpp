// Simple Shooter Game.


#include "AI/SSBaseAICharacter.h"

#include "AI/SSAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASSBaseAICharacter::ASSBaseAICharacter(const FObjectInitializer& ObjInt):Super(ObjInt)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASSAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

