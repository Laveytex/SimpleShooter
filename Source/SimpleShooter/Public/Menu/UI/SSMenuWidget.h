// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	
	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void OnStartGame();
};
