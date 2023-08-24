// Simple Shooter Game.


#include "Weapon/SSRifleWeapon.h"

#include "Engine/DamageEvents.h"
#include "Weapon/Components/SSWeaponFXComponent.h"

ASSRifleWeapon::ASSRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USSWeaponFXComponent>("WeaponFXComponent");
}

void ASSRifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASSRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASSRifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	
	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false,
			   3.0f, 0, 3.f);

		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false,
		3.0f, 0, 3.f);
	}
	
	DecreaseAmmo();
}

bool ASSRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return  false;
 	
	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpreed);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad); //SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASSRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

