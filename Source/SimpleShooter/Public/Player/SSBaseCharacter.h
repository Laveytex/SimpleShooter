// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/SSWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSBaseCharacter.generated.h"


class USSHealthComponent;
class USSWeaponComponent;

UCLASS()
class SIMPLESHOOTER_API ASSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USSHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USSWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(700.f, 1200.f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";

	virtual void OnDeath();

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;


	void SetPlayerColor(const FLinearColor& Color) const;

private:
	void OnHealthChanged(float Health, float HealthDelta) const;

	UFUNCTION()
	void OnGroundLanded(const FHitResult& HitResult);
};
