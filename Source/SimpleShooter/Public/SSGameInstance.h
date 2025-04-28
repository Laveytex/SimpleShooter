// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCoreTypes.h"
#include "Engine/GameInstance.h"
#include "SSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelData& LevelData) { StartupLevel = LevelData; }

	TArray<FLevelData> GetLevelsData() const { return LevelsData; }
	FName GetMenuLevelName() const { return MenuLevelName; }

	void ToggleVolume();

protected:
	UPROPERTY(EditAnywhere, Category = "Game")
	TArray<FLevelData> LevelsData;
	UPROPERTY(EditAnywhere, Category = "Game")
	FName MenuLevelName = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundClass* MasterSoundClass;

private:
	FLevelData StartupLevel;
};
