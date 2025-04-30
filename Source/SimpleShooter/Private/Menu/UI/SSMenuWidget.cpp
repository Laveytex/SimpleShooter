// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSMenuWidget.h"

#include "SSGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/SSLevelItemWidget.h"

void USSMenuWidget::OpenGameCreatWidget()
{
	
}

void USSMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USSMenuWidget::OnQuitGame);
	}
	if (OpenGameCreateButton)
	{
		OpenGameCreateButton->OnClicked.AddDynamic(this, &USSMenuWidget::OpenGameCreatWidget);
	}
}



void USSMenuWidget::OnQuitGame()
{
	if (!GetWorld()) return;
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
