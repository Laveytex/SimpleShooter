// Simple Shooter Game.


#include "Components/SSWeaponComponent.h"

#include "Animations/SSEquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/SSBaseWeapon.h"


USSWeaponComponent::USSWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void USSWeaponComponent::StartFire()
{
	if (!CanFire()) return;
	
	CurrentWeapon->StartFire();
}

void USSWeaponComponent::StopFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StopFire();
}

void USSWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;
	
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapons(CurrentWeaponIndex);
}


void USSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
	SpawnWeapons();
	EquipWeapons(CurrentWeaponIndex);
}

void USSWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
		
	Super::EndPlay(EndPlayReason);
}


void USSWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld()) return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASSBaseWeapon>(WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
	
}

void USSWeaponComponent::AttachWeaponToSocket(ASSBaseWeapon* Weapon, USkeletalMeshComponent* Mesh, const FName& SocketName)
{
	if (!Weapon || !Mesh) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
}

void USSWeaponComponent::EquipWeapons(int32 WeaponIndex)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInPrograss = true;
	PlayAnimMontage(EquipAnimMontage);
}

void USSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->PlayAnimMontage(Animation);
}

void USSWeaponComponent::InitAnimations()
{
	if (!EquipAnimMontage) return;
	const auto NotifieEvents = EquipAnimMontage->Notifies;

	for (auto NotifieEvent : NotifieEvents)
	{
		auto EquipFinishedNotify =  Cast<USSEquipFinishedAnimNotify>(NotifieEvent.Notify);
		if (EquipFinishedNotify)
		{
			EquipFinishedNotify->OnNotified.AddUObject(this, &USSWeaponComponent::OnEquipFinished);
			break;
		}
	}
}

void USSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Equip finished"));
	EquipAnimInPrograss = false;
}

bool USSWeaponComponent::CanFire() const
{
	return !EquipAnimInPrograss && CurrentWeapon;
}

bool USSWeaponComponent::CanEquip() const
{
	return !EquipAnimInPrograss;
}


