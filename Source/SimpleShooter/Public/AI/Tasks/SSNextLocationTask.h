// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SSNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USSNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,	Category = "AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,	Category = "AI")
	FBlackboardKeySelector AimLocationKey;
};
