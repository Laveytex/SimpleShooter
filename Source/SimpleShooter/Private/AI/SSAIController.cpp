// Simple Shooter Game.


#include "AI/SSAIController.h"
#include "AI/SSBaseAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SSAIPerceptionComponent.h"


ASSAIController::ASSAIController()
{
	
	SSPerceptionComponent = CreateDefaultSubobject<USSAIPerceptionComponent>("SSPerceptionComponent");
	SetPerceptionComponent(*SSPerceptionComponent);

	bWantsPlayerState = true;
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

	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor); 
}

AActor* ASSAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
