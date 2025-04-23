// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/SSMenuPlayerController.h"

void ASSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
