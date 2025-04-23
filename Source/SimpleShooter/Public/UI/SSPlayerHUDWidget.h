// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/SSHealthComponent.h"
#include "SSPlayerHUDWidget.generated.h"



UCLASS()
class SIMPLESHOOTER_API USSPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* Pawn);
};
