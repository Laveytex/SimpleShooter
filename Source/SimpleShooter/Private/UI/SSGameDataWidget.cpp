// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSGameDataWidget.h"

#include "SSGameModeBase.h"
#include "Player/SSPlayerState.h"

int32 USSGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMod = GetSSGameMod();
	return GameMod ? GameMod->GetCurrentRoundNum() : 0;
}

int32 USSGameDataWidget::GetTotalRoundNum() const
{
	const auto GameMod = GetSSGameMod();
	return GameMod ? GameMod->GetGameDate().RoundsNum : 0;
}

int32 USSGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMod = GetSSGameMod();
	return GameMod ? GameMod->GetRoundSecondsRemaining() : 0;
}

ASSGameModeBase* USSGameDataWidget::GetSSGameMod() const
{
	return GetWorld() ? Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASSPlayerState* USSGameDataWidget::GetSSPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASSPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
