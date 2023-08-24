// Simple Shooter Game.


#include "Components/SSWeaponComponent.h"

#include "Animations/AnimUtils.h"
#include "Animations/SSEquipFinishedAnimNotify.h"
#include "Animations/SSReloadFinishedAnimNotify.h"
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

void USSWeaponComponent::Reload()
{
	ChangeClip();
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

	for (auto OneWeaponData : WeaponData)
	{
		auto Weapon = GetWorld()->SpawnActor<ASSBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->OnClipeEmpty.AddUObject(this, &USSWeaponComponent::OnEmpryClip);
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
	if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
		{ return Data.WeaponClass == CurrentWeapon->GetClass();});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
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
	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USSEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify)
	{
		EquipFinishedNotify->OnNotified.AddUObject(this, &USSWeaponComponent::OnEquipFinished);
	}

	for (auto OneWeaponData : WeaponData)
	{
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USSReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
		
		if (!ReloadFinishedNotify) continue;
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USSWeaponComponent::OnReloadFinished);
	}
}

void USSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;
	EquipAnimInPrograss = false;
}

void USSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;
	ReloadAnimInPrograss = false;
}

bool USSWeaponComponent::CanReload() const
{
	return !EquipAnimInPrograss
	&& CurrentWeapon
	&& !ReloadAnimInPrograss
	&& CurrentWeapon->CanReload();
}

void USSWeaponComponent::OnEmpryClip(ASSBaseWeapon* EmptyWeapon)
{
	if(!EmptyWeapon) return;
	
	if (CurrentWeapon == EmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for( const auto Weapon : Weapons)
		{
			if (Weapon == EmptyWeapon)
			{
				ChangeClip();
			}
		}
	}
}

void USSWeaponComponent::ChangeClip()
{
	if(!CanReload()) return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	ReloadAnimInPrograss = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USSWeaponComponent::CanFire() const
{
	return !EquipAnimInPrograss && CurrentWeapon && !ReloadAnimInPrograss;
}

bool USSWeaponComponent::CanEquip() const
{
	return !EquipAnimInPrograss && !ReloadAnimInPrograss;
}

bool USSWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if(CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool USSWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if(CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetAmmoData();
		return true;
	}
	return false;
}

bool USSWeaponComponent::TryToAddAmmo(TSubclassOf<ASSBaseWeapon> WeaponType, int32 ClipAmount)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return Weapon->TryToAddAmmo(ClipAmount);
		}
	}
	return false;
}
