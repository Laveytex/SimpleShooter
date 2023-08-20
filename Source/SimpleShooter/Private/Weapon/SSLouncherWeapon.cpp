// Simple Shooter Game.


#include "Weapon/SSLouncherWeapon.h"

#include "Kismet/GameplayStatics.h"

void ASSLouncherWeapon::StartFire()
{
	MakeShot();
}

void ASSLouncherWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return;
	
	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform (FRotator::ZeroRotator, GetMuzzleWorldLocation());
	//auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	ASSProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASSProjectile>(ProjectileClass, SpawnTransform);
	if(Projectile)
	{
		Projectile->SetShotDirecton(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}
	//UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

	DecreaseAmmo();
}
