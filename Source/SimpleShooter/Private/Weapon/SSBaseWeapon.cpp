 // Simple Shooter Game.


#include "Weapon/SSBaseWeapon.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

 ASSBaseWeapon::ASSBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(WeaponMesh);
}

 void ASSBaseWeapon::StartFire()
 {
 }

void ASSBaseWeapon::StopFire()
 {
 }

 void ASSBaseWeapon::Zoom(bool Enable)
 {
 }

 void ASSBaseWeapon::PlayEquipSound()
 {
 	if(!GetWorld()) return;
 	UGameplayStatics::PlaySound2D(this, WeaponEquipSound);
 }

 bool ASSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
 {
	const auto SSCharacter = Cast<ACharacter>(GetOwner());
 	if(!SSCharacter) return false;

	if (SSCharacter->IsPlayerControlled())
	{
		const auto  Controller = SSCharacter->GetController<APlayerController>();
		if(!Controller) return false;
		
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
 	
 	return true;
 }

 FVector ASSBaseWeapon::GetMuzzleWorldLocation() const
 {
 	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
 }

 bool ASSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
 {
 	FVector ViewLocation;
 	FRotator ViewRotation;
 	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return  false;
 	
	TraceStart = ViewLocation; //SocketTransform.GetLocation();

 	//TraceStart = WeaponMesh->GetSocketLocation(MuzzleSocketName);
 	const FVector ShootDirection = ViewRotation.Vector(); //SocketTransform.GetRotation().GetForwardVector();
 	//const FVector ShootDirection = WeaponMesh->GetSocketRotation(MuzzleSocketName).Vector(); //SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
 }

 void ASSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
 {
 	if(!GetWorld()) return;
 	FCollisionQueryParams CollisionParams;
 	CollisionParams.bReturnPhysicalMaterial = true;
 	CollisionParams.AddIgnoredActor(GetOwner());
 	
 	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
 }

 void ASSBaseWeapon::DecreaseAmmo()
 {
 	if(CurrentAmmo.Bullets == 0) return;
 	CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
    	StopFire();
    	OnClipEmpty.Broadcast(this);
    }
 }

 bool ASSBaseWeapon::IsAmmoEmpty() const
 {
 	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
 }

 bool ASSBaseWeapon::IsClipEmpty() const
 {
 	return CurrentAmmo.Bullets == 0;
 }

 bool ASSBaseWeapon::IsAmmoFull() const
 {
 	return CurrentAmmo.Clips == DefaultAmmo.Clips &&
 		CurrentAmmo.Bullets == DefaultAmmo.Bullets;
 }

 void ASSBaseWeapon::ChangeClip()
 {
 	
    if (!CurrentAmmo.Infinite)
    {
    	if(CurrentAmmo.Clips == 0) return;
	    CurrentAmmo.Clips--;
    }
 	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
 }

 bool ASSBaseWeapon::CanReload() const
 {
 	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
 }

 bool ASSBaseWeapon::TryToAddAmmo(const int32 ClipsAmount)
 {
 	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if (IsAmmoEmpty())
    {
	   CurrentAmmo.Clips =  FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
    	OnClipEmpty.Broadcast(this);
    }
 	else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
	    const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
 		if(DefaultAmmo.Clips - NextClipsAmount >= 0)
 		{
 			CurrentAmmo.Clips = NextClipsAmount;
 		}
        else
        {
        	CurrentAmmo.Clips = DefaultAmmo.Clips;
        	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        }
    }
    else
    {
	    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
 	return true;
 }

 UNiagaraComponent* ASSBaseWeapon::SpawnMuzzleFX() const
 {
	return 	UNiagaraFunctionLibrary::SpawnSystemAttached
 	(MuzzleFX, WeaponMesh, MuzzleSocketName,
 		FVector::ZeroVector, FRotator::ZeroRotator,
 		EAttachLocation::SnapToTarget, true);
 }

 void ASSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
 	CurrentAmmo = DefaultAmmo;
 }

 void ASSBaseWeapon::MakeShot()
 {
	 if (IsAmmoEmpty() && GetWorld())
	 {
		 UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
	 }
 }
