// Simple Shooter Game.


#include "AI/Services/SSFireService.h"

#include "AIController.h"
#include "SSUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SSWeaponComponent.h"

USSFireService::USSFireService()
{
	NodeName = "Fire";
}

void USSFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKay.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
