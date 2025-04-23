// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSGoToMenuWidget.h"

#include "SSGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USSGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USSGoToMenuWidget::OnGoToMenu);
	}
}

void USSGoToMenuWidget::OnGoToMenu()
{
	if(!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<USSGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetStartupLevelName().IsNone()) return;
	
	UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}
