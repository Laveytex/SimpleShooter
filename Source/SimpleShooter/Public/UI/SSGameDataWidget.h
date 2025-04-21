// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSGameDataWidget.generated.h"

class ASSPlayerState;
class ASSGameModeBase;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	ASSGameModeBase* GetSSGameMod() const;
	ASSPlayerState* GetSSPlayerState() const;
};
