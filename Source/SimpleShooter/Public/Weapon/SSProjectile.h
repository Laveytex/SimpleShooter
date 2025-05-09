// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SSWeaponComponent.h"
#include "Components/SSWeaponFXComponent.h"
#include "GameFramework/Actor.h"
#include "SSProjectile.generated.h"

class CollisionComponent;
class UProjectileMovementComponent;
class USSWeaponComponent;


UCLASS()
class SIMPLESHOOTER_API ASSProjectile : public AActor
{
	GENERATED_BODY()

public:
	ASSProjectile();

	void SetShotDirecton(const FVector& Direction) { ShotDirection = Direction; };

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* TraceFX;
	
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	USSWeaponFXComponent* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* ProjectileSound;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeTime = 1.0f;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;

	UPROPERTY()
	UNiagaraComponent* TraceFXComponent;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
	                     AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	                     const FHitResult& Hit);

	AController* GetController() const;
	void InitFX();
	UNiagaraComponent* SpawnFX() const;

	UPROPERTY()
	UAudioComponent* ProjectileAudioComponent;

	UFUNCTION()
	void OnNiagaraFinished(UNiagaraComponent* Component);

	bool bHasHit = false;
};
