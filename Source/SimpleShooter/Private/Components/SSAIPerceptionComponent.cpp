// Simple Shooter Game.


#include "Components/SSAIPerceptionComponent.h"

#include "SSUtils.h"
#include "AI/SSAIController.h"
#include "Components/SSHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USSAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		if (!PercieveActor) continue; // Проверка на nullptr

		const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(PercieveActor);
		if (!HealthComponent || HealthComponent->IsDead()) continue; // Проверка на пустой компонент и мертвого игрока

		const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (CurrentDistance < BestDistance)
		{
			BestDistance = CurrentDistance;
			BestPawn = PercieveActor;
		}
	}

	return BestPawn;
}
