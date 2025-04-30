// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/WeaponReloadSoundAnimNotify.h"

#include "SSUtils.h"
#include "Components/SSWeaponComponent.h"
#include "Kismet/GameplayStatics.h"

class USSWeaponComponent;
void UWeaponReloadSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!SoundToPlay || !MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	USSWeaponComponent* WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(Owner);
	if (WeaponComponent)
	{
		WeaponComponent->OnWeaponReloadSound(MeshComp, SoundToPlay);
	}
	Super::Notify(MeshComp, Animation);
}
