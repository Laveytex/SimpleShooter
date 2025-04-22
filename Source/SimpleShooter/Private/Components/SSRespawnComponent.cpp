// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SSRespawnComponent.h"

#include "SSGameModeBase.h"

// Sets default values for this component's properties
USSRespawnComponent::USSRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USSRespawnComponent::Respawn(const int32 RespawnTime)
{
	if(!GetWorld()) return;
	
	RespawnTimeCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USSRespawnComponent::UpdateRespawnTime, 1.f, true);
}

bool USSRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void USSRespawnComponent::UpdateRespawnTime()
{
	
	if (--RespawnTimeCountDown == 0)
	{
		if(!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMod = Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());

		if (!GameMod) return;

		GameMod->RespawnRequest(Cast<AController>(GetOwner()));

	}
}

