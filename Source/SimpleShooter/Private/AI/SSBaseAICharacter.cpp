// Simple Shooter Game.


#include "AI/SSBaseAICharacter.h"

#include "AI/SSAIController.h"

ASSBaseAICharacter::ASSBaseAICharacter(const FObjectInitializer& ObjInt):Super(ObjInt)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASSAIController::StaticClass();
}
