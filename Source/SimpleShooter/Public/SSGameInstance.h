// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FString TestString = "Hello";
};
