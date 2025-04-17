// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/SSAmmoPercentDecorator.h"

#include "AIController.h"
#include "SSUtils.h"
#include "Components/SSWeaponComponent.h"

USSAmmoPercentDecorator::USSAmmoPercentDecorator()
{
	NodeName = "AmmoPercent";
}

bool USSAmmoPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (!Controller) return false;

	const auto WeaponComponent = SSUtils::GetSSPlayerComponent<USSWeaponComponent>(Controller->GetPawn());

	if (!WeaponComponent) return false;
	
	return WeaponComponent->NeedAmmo(WeaponType);;
}
