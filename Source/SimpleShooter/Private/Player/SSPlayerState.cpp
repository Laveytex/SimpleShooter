// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LOGSSPlayerState, All, All)

void ASSPlayerState::LogInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("TeamID: %u, Kills: %u, Death: %u"), TeamID, KillsNum, DeathsNum);
}
