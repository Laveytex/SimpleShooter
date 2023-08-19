// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SSProjectile.generated.h"

class CollisionComponent;
class UProjectileMovementComponent;

UCLASS()
class SIMPLESHOOTER_API ASSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASSProjectile();
	
	void SetShotDirecton(const FVector& Direction){ ShotDirection = Direction; };

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeTime = 5.0f;
	
	virtual void BeginPlay() override;

	
private:
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit( UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};
