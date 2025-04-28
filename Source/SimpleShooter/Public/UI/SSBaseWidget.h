// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSBaseWidget.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Show();

	virtual void OnStartPlaySound() const;

protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* OpenWidgetSound;
};
