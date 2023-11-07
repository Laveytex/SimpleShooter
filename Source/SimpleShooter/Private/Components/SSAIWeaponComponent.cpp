// Simple Shooter Game.


#include "Components/SSAIWeaponComponent.h"
#include "Weapon/SSBaseWeapon.h"

void USSAIWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	if (CurrentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurrentWeapon->StartFire();
	}
}

void USSAIWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	while (NextIndex != CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}
	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapons(CurrentWeaponIndex);
	}
}
