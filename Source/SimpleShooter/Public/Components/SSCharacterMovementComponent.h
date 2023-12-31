// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifire = 2.0f;
	
	virtual float GetMaxSpeed() const override;
};
