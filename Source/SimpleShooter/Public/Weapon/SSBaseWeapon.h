// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "GameFramework/Actor.h"
#include "SSBaseWeapon.generated.h"


class USoundCue;
class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;



UCLASS()
class SIMPLESHOOTER_API ASSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASSBaseWeapon();
	
	FOnClipeEmptySigyature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();
	virtual void Zoom(bool Enable);

	virtual void PlayEquipSound();

	void ChangeClip();
	bool CanReload() const;

	FWeaponUIData GetUIData() const { return  UIData; }
	
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoFull() const;
	bool IsAmmoEmpty() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleFlashSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 3500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo {15, 10, false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* WeaponEquipSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* NoAmmoSound;
	
	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	virtual  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

	void DecreaseAmmo();
	
	bool IsClipEmpty() const;
	
	UNiagaraComponent* SpawnMuzzleFX() const;
	
private:
	FAmmoData CurrentAmmo;
	
	
};
