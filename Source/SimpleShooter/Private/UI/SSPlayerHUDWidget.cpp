// Simple Shooter Game.


#include "UI/SSPlayerHUDWidget.h"

#include "SSUtils.h"
#include "Components/SSHealthComponent.h"
#include "Components/SSWeaponComponent.h"

float USSPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USSPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USSPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USSPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USSPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

