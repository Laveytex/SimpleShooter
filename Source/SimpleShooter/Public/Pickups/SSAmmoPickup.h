// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SSBasePickup.h"
#include "Weapon/SSBaseWeapon.h"
#include "SSAmmoPickup.generated.h"

class ASSBaseWeapon;

UCLASS()
class SIMPLESHOOTER_API ASSAmmoPickup : public ASSBasePickup
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<ASSBaseWeapon> WeaponType;

	
public:
	
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
