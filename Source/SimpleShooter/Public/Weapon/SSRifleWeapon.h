// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSRifleWeapon : public ASSBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.2f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpreed = 1.5f;
	
	virtual void MakeShot() override;
	virtual  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;

private:
	FTimerHandle ShotTimerHandle;
};
