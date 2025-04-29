// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "Components/ActorComponent.h"
#include "SSHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSHealthComponent();

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	bool TryToAddHealth(int32 HealthAmount);
	bool IsHealthFull() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "200.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 0.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealthDelay = 3.3f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	TMap<UPhysicalMaterial*, float> DamageModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Health = 0.0f;

	float HealTime = HealthDelay;

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser );
	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, AActor* DamageCauser );
	UFUNCTION()
	void OnTakeAnyDamage (AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle HealTimerHandle;

	void HealUpdate();
	void SetHealth(float NewHealth);

	void PlayCameraShake() const;

	void Killed(const AController* KillerController) const;
	void ApplyDamage(float Damage, const AController* InstigatedBy);
	void ReportDamageEvent(float Damage, const AController* InstigatedController) const;

	float GetPointDamageModifire(AActor* DamagedActor, const FName& BoneName);
};
