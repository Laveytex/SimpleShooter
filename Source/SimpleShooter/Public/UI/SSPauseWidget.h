// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "SSPauseWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSPauseWidget : public USSBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

private:
	UFUNCTION()
	void OnClearPause();
};
