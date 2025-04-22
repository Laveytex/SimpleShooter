// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSPauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool USSPauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USSPauseWidget::OnClearPause);
	}

	return InitStatus;
}

void USSPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
