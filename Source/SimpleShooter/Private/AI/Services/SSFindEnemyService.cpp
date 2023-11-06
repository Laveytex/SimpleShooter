// Simple Shooter Game.


#include "AI/Services/SSFindEnemyService.h"

#include "SSUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SSAIPerceptionComponent.h"

USSFindEnemyService::USSFindEnemyService()
{
	NodeName = "FindEnemy";
}

void USSFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackbord = OwnerComp.GetBlackboardComponent();
	if (Blackbord)
	{
		const auto Controller = OwnerComp.GetOwner();
		const auto PerceptionComponent = SSUtils::GetSSPlayerComponent<USSAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackbord->SetValueAsObject(EnemyKay.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
