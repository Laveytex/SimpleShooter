// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSPauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void USSPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USSPauseWidget::OnClearPause);
	}
}

void USSPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
