 // Simple Shooter Game.


#include "Weapon/SSBaseWeapon.h"

#include "Engine/DamageEvents.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"


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
 	const auto  Controller = GetPlayerController();
 	if(!Controller) return false;
 	
 	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
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
 	CollisionParams.AddIgnoredActor(GetOwner());
 	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

 	
 }

 void ASSBaseWeapon::DecreaseAmmo()
 {
 	if(CurrentAmmo.Bullets == 0) return;
 	CurrentAmmo.Bullets--;
 	LogAmmo();

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
    	StopFire();
    	OnClipeEmpty.Broadcast();
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

 void ASSBaseWeapon::LogAmmo()
 {

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
