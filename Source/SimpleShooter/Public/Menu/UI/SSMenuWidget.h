// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/SSBaseWidget.h"
#include "SSMenuWidget.generated.h"

class USSGameInstance;
struct FLevelData;
class USSLevelItemWidget;
class UHorizontalBox;
class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSMenuWidget : public USSBaseWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* OpenGameCreateButton;

	UPROPERTY(meta = (BindWidget))
	UButton* GameOptionsButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnQuitGame();

	UFUNCTION()
	void OpenGameCreatWidget();
};
