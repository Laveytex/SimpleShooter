// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "SSGameOverWidget.generated.h"


class UButton;
enum class ESSMatchState : uint8;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSGameOverWidget : public USSBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetLevelButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChange(ESSMatchState State);
	void UpdatePlayerStat() const;

	UFUNCTION()
	void OnResetLevel();
};
