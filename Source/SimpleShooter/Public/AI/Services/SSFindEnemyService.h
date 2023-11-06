// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SSFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USSFindEnemyService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyKay;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
