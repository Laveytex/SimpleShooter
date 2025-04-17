// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/SSHealthPercentDecorator.h"
#include "AIController.h"
#include "SSUtils.h"
#include "Components/SSHealthComponent.h"

USSHealthPercentDecorator::USSHealthPercentDecorator()
{
	NodeName = "HealthPercent";
}

bool USSHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	const auto HealthComponent = SSUtils::GetSSPlayerComponent<USSHealthComponent>(Controller->GetPawn());
	if(!HealthComponent || HealthComponent->IsDead()) return false;
	
	return HealthComponent->GetHealth() <= HealthPercent;
}
