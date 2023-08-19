// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SIMPLESHOOTER_API ASSBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASSBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleFlashSocket";
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;
	
	virtual void BeginPlay() override;

	virtual void MakeShot();
	
	APlayerController* GetPlayerController();
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);

	FVector GetMuzzleWorldLocation() const;

	virtual  bool GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);


private:
	FTimerHandle ShotTimerHandle;
};
