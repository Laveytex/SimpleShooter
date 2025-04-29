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
	
	virtual void StartFire();
	void StopFire();
	virtual void NextWeapon();
	void Reload();

	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

	bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

	bool TryToAddAmmo(TSubclassOf<ASSBaseWeapon> WeaponType, int32 ClipAmount);
	bool NeedAmmo(TSubclassOf<ASSBaseWeapon> WeaponType);

	void Zoom(bool Enable);
	void UnEquip();

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

	UPROPERTY()
	ASSBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASSBaseWeapon*> Weapons;

	bool CanFire() const;
	bool CanEquip() const;
	
	int32 CurrentWeaponIndex = 0;
	void EquipWeapons(int32 WeaponIndex);

private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;
	
	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;

	UPROPERTY()
	UAudioComponent* ReloadSoundComponent;
	
	void SpawnWeapons();
	static void AttachWeaponToSocket(ASSBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName& SocketName);

	void PlayAnimMontage(UAnimMontage* Animation) const;
	
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	void OnWeaponReloadSoundTriggered(USkeletalMeshComponent* SkeletalMeshComponent, USoundBase* SoundBase);
	
	bool CanReload() const;

	void OnEmptyClip(ASSBaseWeapon* EmptyWeapon);
	void ChangeClip();
	void BreakReload();
	void StopReloadSound() const;
};
