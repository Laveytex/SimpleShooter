// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SSBaseWidget.h"
#include "SSGameCreateWidget.generated.h"

class USSGameInstance;
struct FLevelData;
class USSLevelItemWidget;
class UHorizontalBox;
class UButton;

UCLASS()
class SIMPLESHOOTER_API USSGameCreateWidget : public USSBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* LevelItemsBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	USoundCue* ButtonStartSound;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HideAnimation;
	
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	TArray<USSLevelItemWidget*> LevelItemsWidgets;
	
	UFUNCTION()
	void OnStartGame();
	
	void InitLevelItems();

	void OnLevelSelected(const FLevelData& Data);

	USSGameInstance* GetSSGameInstance() const;
};
