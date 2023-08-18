// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSWeaponComponent.generated.h"

class ASSBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USSWeaponComponent();
	
	void StartFire();
	void StopFire();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASSBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";
	
	virtual void BeginPlay() override;

public:

private:
	UPROPERTY()
	ASSBaseWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
};
