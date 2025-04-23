// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSMenuWidget.h"

#include "SSGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USSMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USSMenuWidget::OnStartGame);		
	}
}

void USSMenuWidget::OnStartGame()
{
	if(!GetWorld()) return;

	const auto GameInstance = GetWorld()->GetGameInstance<USSGameInstance>();
	if (!GameInstance) return;

	if (GameInstance->GetStartupLevelName().IsNone()) return;

	const FName StartupLevelName = "Level_Test";
	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}
