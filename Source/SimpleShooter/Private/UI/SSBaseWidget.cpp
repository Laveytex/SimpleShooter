// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSBaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


void USSBaseWidget::Show()
{
	PlayAnimation(ShowAnimation);
	OnStartPlaySound();
}

void USSBaseWidget::OnStartPlaySound() const
{
	if (!OpenWidgetSound || !GetWorld()) return;
	UGameplayStatics::PlaySound2D(this, OpenWidgetSound);
}
