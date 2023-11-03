// Simple Shooter Game.


#include "AI/SSAIController.h"
#include "AI/SSBaseAICharacter.h"
#include "Components/SSAIPerceptionComponent.h"


ASSAIController::ASSAIController()
{
	
	SSPerceptionComponent = CreateDefaultSubobject<USSAIPerceptionComponent>("SSPerceptionComponent");
	SetPerceptionComponent(*SSPerceptionComponent);
}

void ASSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	const auto SSCharacter = Cast<ASSBaseAICharacter>(InPawn);
	if(SSCharacter)
	{
		RunBehaviorTree(SSCharacter->BehaviorTreeAsset);
	}
}

void ASSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = SSPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor); 
}
