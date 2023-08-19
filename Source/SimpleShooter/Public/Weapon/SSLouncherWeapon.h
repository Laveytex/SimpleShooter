// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "SSProjectile.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSLouncherWeapon.generated.h"

class ASSProjectile;
UCLASS()
class SIMPLESHOOTER_API ASSLouncherWeapon : public ASSBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ASSProjectile> ProjectileClass;
	
	virtual void MakeShot() override;
	
};
