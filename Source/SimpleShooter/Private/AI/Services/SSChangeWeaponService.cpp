// Simple Shooter Game.


#include "AI/Services/SSChangeWeaponService.h"

#include "AIController.h"
#include "SSUtils.h"
#include "Components/SSWeaponComponent.h"

USSChangeWeaponService::USSChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void USSChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller)
	{
		const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Propability > 0 && FMath::FRand() <= Propability)
		{
			WeaponComponent->NextWeapon();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
