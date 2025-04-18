// Simple Shooter Game.


#include "Pickups/SSBasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

// Sets default values
ASSBasePickup::ASSBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASSBasePickup::BeginPlay()
{
	Super::BeginPlay();

	GenerateRotationYaw();
	
}

void ASSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);

	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
}

// Called every frame
void ASSBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f,RotationYaw, 0.0f));

}

bool ASSBasePickup::CouldBeTaken() const
{
	return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

bool ASSBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASSBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	GetRootComponent()->SetVisibility(false, true);
	
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASSBasePickup::Respawn, RespawnTime);
}

void ASSBasePickup::Respawn()
{
	GenerateRotationYaw();
	
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	GetRootComponent()->SetVisibility(true, true);
}

void ASSBasePickup::GenerateRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

