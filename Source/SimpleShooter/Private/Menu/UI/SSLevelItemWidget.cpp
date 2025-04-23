// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSLevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USSLevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
	}
	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(LevelData.LevelIcon);
	}
}

void USSLevelItemWidget::SetSelected(const bool bSelected) const
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(bSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USSLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectionButton)
	{
		LevelSelectionButton->OnClicked.AddDynamic(this, &USSLevelItemWidget::OnLevelSelectionButtonClicked);
	}
}

void USSLevelItemWidget::OnLevelSelectionButtonClicked()
{
	OnLevelSelection.Broadcast(LevelData);
}
