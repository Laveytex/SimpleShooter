// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSBaseCharacter.h"
#include "SSBaseAICharacter.generated.h"

class UWidgetComponent;
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

	//переделать в таймер
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float HealthVisibilityDistance = 1000.f;
	
	virtual void BeginPlay() override;
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) const override;

private:
	void UpdateHealthWidgetVisibility() const;
};
