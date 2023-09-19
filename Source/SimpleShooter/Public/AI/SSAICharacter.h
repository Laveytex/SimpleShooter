// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSBaseCharacter.h"
#include "SSAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSAICharacter : public ASSBaseCharacter
{
	GENERATED_BODY()

public:
	ASSAICharacter(const FObjectInitializer& ObjInt);
};
