// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "Menu/UI/SSMenuWidget.h"

void ASSMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MainMenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<USSBaseWidget>(GetWorld(), MainMenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}
