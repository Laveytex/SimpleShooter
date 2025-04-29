// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/WeaponReloadSoundAnimNotify.h"

#include "Kismet/GameplayStatics.h"

FOnWeaponReloadSoundNotifySignature UWeaponReloadSoundAnimNotify::OnNotified;

void UWeaponReloadSoundAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (SoundToPlay && MeshComp)
	{
		//UGameplayStatics::SpawnSoundAttached(SoundToPlay, MeshComp);
		OnNotified.Broadcast(MeshComp, SoundToPlay);
	}
	Super::Notify(MeshComp, Animation);
}
