﻿#pragma once
#include "Player/SSPlayerState.h"

class SSUtils
{
public:
	template <typename T>
	static T* GetSSPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
	
	bool static AreEnemies(const AController* Controller1, const AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

		const auto PlayerState1 = Cast<ASSPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<ASSPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}

	static FText TextFromInt(const int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};
