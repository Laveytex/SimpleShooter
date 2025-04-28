// Fill out your copyright notice in the Description page of Project Settings.


#include "SSGameInstance.h"

#include "Sound/SSSoundFunctionLibrary.h"

void USSGameInstance::ToggleVolume()
{
	USSSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
