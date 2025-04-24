// Simple Shooter Game.


#include "UI/SSPlayerHUDWidget.h"

#include "SSUtils.h"
#include "Components/ProgressBar.h"
#include "Components/SSHealthComponent.h"
#include "Components/SSWeaponComponent.h"

void USSPlayerHUDWidget::NativeOnInitialized()
{
	if (GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USSPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

float USSPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USSPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USSPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;

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

int32 USSPlayerHUDWidget::GetKillsNum() const
{
	const auto PlayerState = GetSSPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USSPlayerHUDWidget::GetDeathNum() const
{
	const auto PlayerState = GetSSPlayerState();
	return PlayerState ? PlayerState->GetDeathsNum() : 0;
}


void USSPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta < 0.0f)
	{
		OnTakeDamage();
	}
	UpdateHealthBar();
}

void USSPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(Pawn);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USSPlayerHUDWidget::OnHealthChanged);
	}
	UpdateHealthBar();
}

ASSPlayerState* USSPlayerHUDWidget::GetSSPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}

void USSPlayerHUDWidget::UpdateHealthBar()
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
	}
}
