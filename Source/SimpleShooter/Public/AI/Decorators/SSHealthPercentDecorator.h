// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SSHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API USSHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	USSHealthPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, Blueprintable, Category = "AI")
	float HealthPercent = 0.6f;
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
