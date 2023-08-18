 // Simple Shooter Game.


#include "Weapon/SSBaseWeapon.h"

#include "Engine/DamageEvents.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "Player/SSBaseCharacter.h"


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

 void ASSBaseWeapon::MakeDamage(const FHitResult& HitResult)
 {
 	const auto DamagedActor = HitResult.GetActor();
 	if (!DamagedActor) return;
 	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
 }


 void ASSBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

 void ASSBaseWeapon::MakeShot()
 {

 }
