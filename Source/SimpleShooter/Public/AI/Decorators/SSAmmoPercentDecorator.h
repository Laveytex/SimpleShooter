// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SSAmmoPercentDecorator.generated.h"

class ASSBaseWeapon;

UCLASS()
class SIMPLESHOOTER_API USSAmmoPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USSAmmoPercentDecorator();

protected:
	UPROPERTY(EditAnywhere, Blueprintable, Category = "AI")
	TSubclassOf<ASSBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
