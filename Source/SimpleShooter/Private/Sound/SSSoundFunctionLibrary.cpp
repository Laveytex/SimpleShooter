// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/SSSoundFunctionLibrary.h"

#include "Sound/SoundClass.h"

void USSSoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, const float Volume)
{
	if (!SoundClass) return;
	SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.f, 1.f); ;
}

void USSSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;

	const auto NextVolume = SoundClass->Properties.Volume > 0.f ? 0.f : 1.f;
	
	SetSoundClassVolume(SoundClass, NextVolume);
}
