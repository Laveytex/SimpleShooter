// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/SSMenuGameModeBase.h"

#include "Menu/SSMenuPlayerController.h"
#include "Menu/UI/SSMenuHUD.h"

ASSMenuGameModeBase::ASSMenuGameModeBase()
{
	PlayerControllerClass = ASSMenuPlayerController::StaticClass();
	HUDClass = ASSMenuHUD::StaticClass();
}
