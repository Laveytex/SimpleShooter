// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSPlayerStatRowsWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USSPlayerStatRowsWidget::SetPlayerName(const FText& Text) const
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USSPlayerStatRowsWidget::SetKills(const FText& Text) const
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void USSPlayerStatRowsWidget::SetDeath(const FText& Text) const
{
	if(!DeathTextBlock) return;
	DeathTextBlock->SetText(Text);
}

void USSPlayerStatRowsWidget::SetTeam(const FText& Text) const
{
	if(!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void USSPlayerStatRowsWidget::SetTeamColor(const FLinearColor& Color) const
{
	if(!TeamImage) return;
	TeamImage->SetColorAndOpacity(Color);
}

void USSPlayerStatRowsWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
