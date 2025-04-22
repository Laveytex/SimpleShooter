// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSSpectatorWidget.h"

#include "SSUtils.h"
#include "Components/SSRespawnComponent.h"

bool USSSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = SSUtils::GetSSPlayerComponent<USSRespawnComponent>(GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
