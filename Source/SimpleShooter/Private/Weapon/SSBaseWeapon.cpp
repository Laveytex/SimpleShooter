 // Simple Shooter Game.


#include "Weapon/SSBaseWeapon.h"

#include "Engine/DamageEvents.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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

 APlayerController* ASSBaseWeapon::GetPlayerController()
 {
 	const auto Player = Cast<ACharacter>(GetOwner());
 	if (!Player) return nullptr;
 	
	return Player->GetController<APlayerController>();
 	
 }

 bool ASSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
 {
	const auto SSCharacter = Cast<ACharacter>(GetOwner());
 	if(!SSCharacter) return false;

	if (SSCharacter->IsPlayerControlled())
	{
		const auto  Controller = GetPlayerController();
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

 	const FVector ShootDirection = ViewRotation.Vector(); //SocketTransform.GetRotation().GetForwardVector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
 }

 void ASSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
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
    	OnClipeEmpty.Broadcast(this);
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
    	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    	FString::Printf(TEXT("-----ClipChanged-----")));
    }
 	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
 }

 bool ASSBaseWeapon::CanReload() const
 {
 	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
 }

 bool ASSBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
 {
 	if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <=0) return false;

    if (IsAmmoEmpty())
    {
	   CurrentAmmo.Clips =  FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
    	OnClipeEmpty.Broadcast(this);
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

 void ASSBaseWeapon::LogAmmo()
 {

 }

 UNiagaraComponent* ASSBaseWeapon::SpawnMuzzleFX()
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
 	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s = FloatVariable"), DefaultAmmo.Bullets));
}

 void ASSBaseWeapon::MakeShot()
 {

 }
