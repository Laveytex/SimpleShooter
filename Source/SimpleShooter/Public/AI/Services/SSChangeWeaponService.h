// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SSChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
	USSChangeWeaponService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyKay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Propability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
