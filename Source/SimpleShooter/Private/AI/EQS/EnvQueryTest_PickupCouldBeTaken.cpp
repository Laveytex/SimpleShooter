// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/SSBasePickup.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const auto DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	const bool WantsToBeTaken = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		const auto PickupActor = Cast<ASSBasePickup>(ItemActor);
		if (!PickupActor) continue;

		const auto CouldBeTaken = PickupActor->CouldBeTaken();

		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsToBeTaken);
	}
}
