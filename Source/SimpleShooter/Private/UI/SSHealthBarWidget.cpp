// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSHealthBarWidget.h"

#include "Components/ProgressBar.h"

void USSHealthBarWidget::SetHealthPercent(const float Percent) const
{
	if (!HealthProgressBar)return;

	const auto HealthVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
		                              ? ESlateVisibility::Hidden
		                              : ESlateVisibility::Visible;
	HealthProgressBar->SetVisibility(HealthVisibility);

	const auto HealthBarColor = (Percent > PercentColorThreshold)
	? GoodColor : BadColor;

	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}
