// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SSAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetClosestEnemy() const;
	
};
