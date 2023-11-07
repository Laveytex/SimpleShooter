// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Components/SSWeaponComponent.h"
#include "SSAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSAIWeaponComponent : public USSWeaponComponent
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;
	virtual void NextWeapon() override;

	
};
