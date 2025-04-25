// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "SSLevelItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	FOnLevelSelectionSignature OnLevelSelection;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const { return LevelData; }

	void SetSelected(bool bSelected) const;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta = (BindWidget))
	UImage* FrameImage;

	UPROPERTY(meta = (BindWidget))
	UButton* LevelSelectionButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelNameTextBlock;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelSelectionButtonClicked();

	UFUNCTION()
	void OnLevelItemHovered();

	UFUNCTION()
	void OnLevelItemUnHovered();
};
