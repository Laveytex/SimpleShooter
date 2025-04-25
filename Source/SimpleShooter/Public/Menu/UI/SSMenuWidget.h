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
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;
	
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	TArray<USSLevelItemWidget*> LevelItemsWidgets;
	
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);

	USSGameInstance* GetSSGameInstance() const;
};
