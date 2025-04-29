// Simple Shooter Game.


#include "Components/SSWeaponComponent.h"

#include "Animations/AnimUtils.h"
#include "Animations/SSEquipFinishedAnimNotify.h"
#include "Animations/SSReloadFinishedAnimNotify.h"
#include "Animations/WeaponReloadSoundAnimNotify.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/SSBaseWeapon.h"

USSWeaponComponent::USSWeaponComponent(): EquipAnimMontage(nullptr)
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
	if (!CanEquip()) return;
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
	for (const auto Weapon : Weapons)
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

		Weapon->OnClipEmpty.AddUObject(this, &USSWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void USSWeaponComponent::AttachWeaponToSocket(ASSBaseWeapon* Weapon, USkeletalMeshComponent* Mesh,
                                              const FName& SocketName)
{
	if (!Weapon || !Mesh) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
}

void USSWeaponComponent::EquipWeapons(const int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
	{
		return;
	}
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
		UnEquip();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];

	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
	{
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	EquipAnimInProgress = true;
	CurrentWeapon->PlayEquipSound();
	PlayAnimMontage(EquipAnimMontage);
}

void USSWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
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
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USSReloadFinishedAnimNotify>(
			OneWeaponData.ReloadAnimMontage);

		if (!ReloadFinishedNotify) continue;
		ReloadFinishedNotify->OnNotified.AddUObject(this, &USSWeaponComponent::OnReloadFinished);
	}

	UWeaponReloadSoundAnimNotify::OnNotified.AddUObject(this, &USSWeaponComponent::OnWeaponReloadSoundTriggered);
}

void USSWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;
	EquipAnimInProgress = false;
}

void USSWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComponent) return;
	ReloadAnimInProgress = false;

	CurrentWeapon->ChangeClip();
}

void USSWeaponComponent::OnWeaponReloadSoundTriggered(USkeletalMeshComponent* SkeletalMeshComponent,
                                                      USoundBase* SoundBase)
{
	if (!SoundBase || !SkeletalMeshComponent) return;

	if (ReloadSoundComponent && ReloadSoundComponent->IsPlaying())
	{
		return;
	}
	ReloadSoundComponent = UGameplayStatics::SpawnSoundAttached(SoundBase, SkeletalMeshComponent);
	UE_LOG(LogTemp, Warning, TEXT("ReloadSound Triggered: %s | %s"),
		*GetNameSafe(SkeletalMeshComponent),
		*GetNameSafe(SoundBase));
}

bool USSWeaponComponent::CanReload() const
{
	return !EquipAnimInProgress
		&& CurrentWeapon
		&& !ReloadAnimInProgress
		&& CurrentWeapon->CanReload();
}

void USSWeaponComponent::OnEmptyClip(ASSBaseWeapon* EmptyWeapon)
{
	if (!EmptyWeapon) return;

	if (CurrentWeapon == EmptyWeapon)
	{
		ChangeClip();
	}
	else
	{
		for (const auto Weapon : Weapons)
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
	if (!CanReload()) return;
	CurrentWeapon->StopFire();

	ReloadAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

void USSWeaponComponent::BreakReload()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	Character->StopAnimMontage(CurrentReloadAnimMontage);
	StopReloadSound();
	ReloadAnimInProgress = false;
	EquipAnimInProgress = false;
}

void USSWeaponComponent::StopReloadSound() const
{
	if (ReloadSoundComponent)
	{
		ReloadSoundComponent->Stop();
	}
}

bool USSWeaponComponent::CanFire() const
{
	return !EquipAnimInProgress && CurrentWeapon && !ReloadAnimInProgress;
}

bool USSWeaponComponent::CanEquip() const
{
	return !EquipAnimInProgress; // && !ReloadAnimInProgress;
}

bool USSWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool USSWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
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

bool USSWeaponComponent::NeedAmmo(const TSubclassOf<ASSBaseWeapon> WeaponType)
{
	for (const auto Weapon : Weapons)
	{
		if (Weapon && Weapon->IsA(WeaponType))
		{
			return !Weapon->IsAmmoFull();
		}
	}
	return false;
}

void USSWeaponComponent::Zoom(const bool Enable)
{
	CurrentWeapon->Zoom(Enable);
}

void USSWeaponComponent::UnEquip()
{
	CurrentWeapon->Zoom(false);
	BreakReload();
}
