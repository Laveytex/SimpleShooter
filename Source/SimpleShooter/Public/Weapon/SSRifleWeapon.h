// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSRifleWeapon.generated.h"

class USSWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class SIMPLESHOOTER_API ASSRifleWeapon : public ASSBaseWeapon
{
	GENERATED_BODY()

public:
	ASSRifleWeapon();
	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpreed = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UNiagaraSystem* TraceFX;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FString TraceTargetName = "TraceTarget";

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USSWeaponFXComponent* WeaponFXComponent;
	
	virtual void MakeShot() override;
	virtual  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

private:
	FTimerHandle ShotTimerHandle;
	
	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	
	void MakeDamage(const FHitResult& HitResult);
	void InitMuzzleFX();
	void SetMuzzleFXVisibility(bool Visible) const;
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;
	
};
