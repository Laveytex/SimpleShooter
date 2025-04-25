// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;
};
