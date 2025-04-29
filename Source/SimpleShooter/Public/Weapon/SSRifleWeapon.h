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
	virtual void Zoom(bool Enable) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpreed = 1.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FOVZoomAngle = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
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

	UPROPERTY()
	UAudioComponent* FireAudioComponent;
	
	void MakeDamage(const FHitResult& HitResult);
	void InitFX();
	void SetFXActive(bool IsActive) const;
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;
	AController* GetController() const;

	float DefaultFOVAngle = 90.0f;
};
