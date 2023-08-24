// Simple Shooter Game.


#include "Pickups/SSHealthPickup.h"

#include "SSUtils.h"
#include "Components/SSHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);


bool ASSHealthPickup::GivePickupTo(APawn* PlayerPawn)
{

	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
	
	//return true;

	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}
