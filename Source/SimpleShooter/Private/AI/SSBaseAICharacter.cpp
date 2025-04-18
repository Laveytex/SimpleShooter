// Simple Shooter Game.


#include "AI/SSBaseAICharacter.h"

#include "BrainComponent.h"
#include "AI/SSAIController.h"
#include "Components/SSAIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASSBaseAICharacter::ASSBaseAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USSAIWeaponComponent>("WeaponAIComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASSAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ASSBaseAICharacter::OnDeath()
{
	const auto SSController = Cast<ASSAIController>(Controller);
	if (SSController && SSController->BrainComponent)
	{
		SSController->BrainComponent->Cleanup();
	}
	Super::OnDeath();
}

