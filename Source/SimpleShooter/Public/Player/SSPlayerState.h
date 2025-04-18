// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSPlayerState : public APlayerState
{
	GENERATED_BODY()

	public:
	void SetTeamID(const int32 ID) { TeamID = ID; }
	int32 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
	FLinearColor GetTeamColor() const { return TeamColor; }
	
private:
	int32 TeamID;
	FLinearColor TeamColor;
};
