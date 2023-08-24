// Simple Shooter Game.


#include "Pickups/SSAmmoPickup.h"

#include "SSUtils.h"
#include "Components/SSHealthComponent.h"
#include "Components/SSWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASSAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(PlayerPawn);
	if(!WeaponComponent) return false;
	
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	
	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
