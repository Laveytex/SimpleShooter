// Simple Shooter Game.


#include "Weapon/SSProjectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/SSWeaponFXComponent.h"

ASSProjectile::ASSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 2000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USSWeaponFXComponent>("WeaponFXComponent");
}

void ASSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASSProjectile::OnProjectileHit);
	SetLifeSpan(LifeTime);

	///
	///
	UNiagaraFunctionLibrary::SpawnSystemAttached
	(TraceFX, CollisionComponent,  FName("SocketName"),
		FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget, true);
}

void ASSProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld()) return;
	MovementComponent->StopMovementImmediately();

	
	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),
		DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this,
		GetController(), DoFullDamage);

	/*DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24,
		FColor::Yellow, false, 5.0f);*/
	WeaponFXComponent->PlayImpactFX(Hit);

	if (TraceFXComponent)
	{
		TraceFXComponent->Deactivate();
		FTimerHandle TimerHandle;
		const float DelayBeforeDestroy = 3.0f;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			Destroy();
		}, DelayBeforeDestroy, false);
	}
}

AController* ASSProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());

	return Pawn ? Pawn->GetController() : nullptr;
}

