// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSBaseCharacter.h"
#include "SSBaseAICharacter.generated.h"

class  UBehaviorTree;

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSBaseAICharacter : public ASSBaseCharacter
{
	GENERATED_BODY()

public:
	ASSBaseAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
};
