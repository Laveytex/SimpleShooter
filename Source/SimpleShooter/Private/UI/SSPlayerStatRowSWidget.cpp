// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSPlayerStatRowSWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USSPlayerStatRowSWidget::SetPlayerName(const FText& Text) const
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USSPlayerStatRowSWidget::SetKills(const FText& Text) const
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void USSPlayerStatRowSWidget::SetDeath(const FText& Text) const
{
	if(!DeathTextBlock) return;
	DeathTextBlock->SetText(Text);
}

void USSPlayerStatRowSWidget::SetTeam(const FText& Text) const
{
	if(!TeamTextBlock) return;
	TeamTextBlock->SetText(Text);
}

void USSPlayerStatRowSWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
	if(!PlayerIndicatorImage) return;
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
