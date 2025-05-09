// Simple Shooter Game.


#include "Components/SSAIPerceptionComponent.h"

#include "SSUtils.h"
#include "AI/SSAIController.h"
#include "Components/SSHealthComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

AActor* USSAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0)
	{
		GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PerceiveActors);
		if (PerceiveActors.Num() == 0) return nullptr;
	} 

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(PerceiveActor);
		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		
		const auto AreEnemies =
			PerceivePawn && SSUtils::AreEnemies(Controller, PerceivePawn->GetController());
		
		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
			{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}
		}
	}

	return BestPawn;
}
