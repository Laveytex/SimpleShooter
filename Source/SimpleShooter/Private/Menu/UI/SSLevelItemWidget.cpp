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



void USSLevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectionButton)
	{
		LevelSelectionButton->OnClicked.AddDynamic(this, &USSLevelItemWidget::OnLevelSelectionButtonClicked);
		LevelSelectionButton->OnHovered.AddDynamic(this, &USSLevelItemWidget::OnLevelItemHovered);
		LevelSelectionButton->OnUnhovered.AddDynamic(this, &USSLevelItemWidget::OnLevelItemUnHovered);
	}
}

void USSLevelItemWidget::OnLevelSelectionButtonClicked()
{
	OnLevelSelection.Broadcast(LevelData);
}

void USSLevelItemWidget::SetSelected(const bool bSelected) const
{
	if (LevelImage)
	{
		LevelImage->SetColorAndOpacity(bSelected ? FLinearColor::Green : FLinearColor::White);
		//LevelImage->SetRenderScale(bSelected ? FVector2d(1.1) : FVector2d(1));
	}
}

void USSLevelItemWidget::OnLevelItemHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void USSLevelItemWidget::OnLevelItemUnHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
