// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSPlayerStatRowsWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSPlayerStatRowsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FText& Text) const;
	void SetKills(const FText& Text) const;
	void SetDeath(const FText& Text) const;
	void SetTeam(const FText& Text) const;
	void SetTeamColor(const FLinearColor& Color) const;
	void SetPlayerIndicatorVisibility(const bool Visible) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathTextBlock;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;

	UPROPERTY(meta = (BindWidget))
	UImage* TeamImage;
};
