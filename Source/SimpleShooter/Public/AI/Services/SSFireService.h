// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SSFireService.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSFireService : public UBTService
{
	GENERATED_BODY()

public:
	USSFireService();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKay;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
