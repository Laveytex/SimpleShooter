// Simple Shooter Game.


#include "Weapon/SSRifleWeapon.h"

void ASSRifleWeapon::StartFire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASSRifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASSRifleWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return;
 	
	//const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	//const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	//const auto CrossProduct = FVector::CrossProduct(SocketTransform.GetRotation().GetForwardVector(), TraceEnd);
	/*const auto AngleBetween = FMath::Acos(FVector::DotProduct
		(TraceStart.GetSafeNormal(), SocketTransform.GetLocation().ForwardVector.GetSafeNormal()));
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);*/

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
 	
	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false,
			   3.0f, 0, 3.f);

		MakeDamage(HitResult);
	 		 	
		/*const auto CrossProduct = FVector::CrossProduct(ShootDirection, SocketTransform.GetRotation().GetForwardVector());
		GEngine->AddOnScreenDebugMessage(-1, 1.0f,
		FColor::Yellow, FString::Printf(TEXT("%s = End "), *CrossProduct.ToString()));*/
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, false,
		3.0f, 0, 3.f);
	}
	
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