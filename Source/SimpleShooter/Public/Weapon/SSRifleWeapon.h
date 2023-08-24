// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSRifleWeapon.generated.h"

class USSWeaponFXComponent;

UCLASS()
class SIMPLESHOOTER_API ASSRifleWeapon : public ASSBaseWeapon
{
	GENERATED_BODY()

public:
	ASSRifleWeapon();
	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.2f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpreed = 1.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USSWeaponFXComponent* WeaponFXComponent;
	
	
	virtual void MakeShot() override;
	virtual  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

	
	void MakeDamage(const FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;
};
