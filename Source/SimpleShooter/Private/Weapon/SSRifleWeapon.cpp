// Simple Shooter Game.


#include "Weapon/SSRifleWeapon.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/Components/SSWeaponFXComponent.h"

ASSRifleWeapon::ASSRifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USSWeaponFXComponent>("WeaponFXComponent");
}

void ASSRifleWeapon::StartFire()
{
	InitFX();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASSRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASSRifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	SetFXActive(false);
}

void ASSRifleWeapon::Zoom(const bool Enable)
{
	const auto Controller = Cast<APlayerController>(GetController());
	if (!Controller || !Controller->PlayerCameraManager) return;

	if (Enable)
	{
		DefaultFOVAngle = Controller->PlayerCameraManager->GetFOVAngle();
	}
	
	Controller->PlayerCameraManager->SetFOV(Enable ? FOVZoomAngle : DefaultFOVAngle);
}

void ASSRifleWeapon::MakeShot()
{
	Super::MakeShot();
	
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	FVector TraceFXEnd = TraceEnd;

	if (HitResult.bBlockingHit)
	{
		TraceFXEnd = HitResult.ImpactPoint;

		MakeDamage(HitResult);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
	DecreaseAmmo();
}

bool ASSRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	const FVector ViewDirection = ViewRotation.Vector();

	// 1. Камера целится в эту точку
	FVector AimPoint = ViewLocation + ViewDirection * TraceMaxDistance;

	// 2. Трассировка от камеры до мира (визуальное прицеливание)
	FHitResult AimHitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(AimHitResult, ViewLocation, AimPoint, ECC_Visibility, Params))
	{
		AimPoint = AimHitResult.ImpactPoint;
	}

	// 3. Старт — из дула
	TraceStart = GetMuzzleWorldLocation();

	// 4. Направление — от дула к AimPoint (с разбросом)
	FVector DesiredDirection = (AimPoint - TraceStart).GetSafeNormal();

	// 5. Проверка угла между направлением камеры и направлением выстрела
	const float AngleDegrees = FMath::RadiansToDegrees(acosf(FVector::DotProduct(ViewDirection, DesiredDirection)));
	const float MaxAllowedAngle = 30.0f; // допустимый угол отклонения

	FVector FinalDirection;
	if (AngleDegrees <= MaxAllowedAngle)
	{
		// Всё нормально — используем отклонённое направление с разбросом
		const float HalfRad = FMath::DegreesToRadians(BulletSpreed);
		FinalDirection = FMath::VRandCone(DesiredDirection, HalfRad);
	}
	else
	{
		// Угол слишком большой — стреляем прямо из дула по направлению камеры
		const float HalfRad = FMath::DegreesToRadians(BulletSpreed);
		FinalDirection = FMath::VRandCone(ViewDirection, HalfRad);
	}

	TraceEnd = TraceStart + FinalDirection * TraceMaxDistance;
	return true;
	
	/*FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation; //SocketTransform.GetLocation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpreed);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	//SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;*/
}

void ASSRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor) return;

	FPointDamageEvent PointDamageEvent;
	PointDamageEvent.HitInfo =  HitResult;
	DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void ASSRifleWeapon::InitFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}

	if (!FireAudioComponent)
	{
		FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	}
	SetFXActive(true);
}

void ASSRifleWeapon::SetFXActive(const bool IsActive) const
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!IsActive);
		MuzzleFXComponent->SetVisibility(IsActive, false);
	}

	if (FireAudioComponent)
	{
		//IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
		FireAudioComponent->SetPaused(!IsActive);
	}
}

void ASSRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const
{
	const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
		TraceFX, TraceStart);
	if (TraceFXComponent)
	{
		TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
	}
}

AController* ASSRifleWeapon::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());

	return Pawn ? Pawn->GetController() : nullptr;
}
