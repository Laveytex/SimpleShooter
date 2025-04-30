// Simple Shooter Game.


#include "Dev/SSDevDamageActor.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ASSDevDamageActor::ASSDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
}

// Called every frame
void ASSDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(),
		Radius, DamageType, {}, this, nullptr, DoFullDamage);
	
}

