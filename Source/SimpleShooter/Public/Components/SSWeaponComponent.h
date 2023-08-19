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
	void NextWeapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASSBaseWeapon>>  WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;
	
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:

private:
	UPROPERTY()
	ASSBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASSBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInPrograss = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ASSBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName& SocketName);
	void EquipWeapons(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
};
