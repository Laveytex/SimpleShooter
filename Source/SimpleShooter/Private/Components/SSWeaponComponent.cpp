// Simple Shooter Game.


#include "Components/SSWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/SSBaseWeapon.h"


USSWeaponComponent::USSWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void USSWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USSWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}


void USSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USSWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	
	CurrentWeapon = GetWorld()->SpawnActor<ASSBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}


