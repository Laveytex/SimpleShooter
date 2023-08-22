// Simple Shooter Game.


#include "Pickups/SSBasePickup.h"

// Sets default values
ASSBasePickup::ASSBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASSBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

