// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SSAIController.generated.h"

class USSAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASSAIController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USSAIPerceptionComponent* SSPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyKey"; 

protected: 
	AActor* GetFocusOnActor() const;
	
};
