// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSGoToMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* GoToMenuButton;

private:
	UFUNCTION()
	void OnGoToMenu();

};
