#pragma once

class SSUtils
{
public:
	template <typename T>
	static T* GetSSPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);;
	}
	
	
};
