// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SSEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyKey";
	//FBlackboardKeySelector EnemyActorKay;
};
