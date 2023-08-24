// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SSCoreTypes.h"
#include "Weapon/SSBaseWeapon.h"
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
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo (TSubclassOf<ASSBaseWeapon> WeaponType, int32 ClipAmount);
	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData>  WeaponData;

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
	
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInPrograss = false;
	bool ReloadAnimInPrograss = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ASSBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName& SocketName);
	void EquipWeapons(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmpryClip(ASSBaseWeapon* EmptyWeapon);
	void ChangeClip();
	
	
};
