// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSMenuWidget.h"

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
	const FName StartupLevelName = "Level_Test";
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
