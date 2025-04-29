// Simple Shooter Game.


#include "Weapon/SSProjectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Weapon/Components/SSWeaponFXComponent.h"

/*FTimerHandle TimerHandle;
		constexpr float DelayBeforeDestroy = 3.0f;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			Destroy();
		}, DelayBeforeDestroy, false);*/

ASSProjectile::ASSProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionComponent->bReturnMaterialOnMove = true;
	SetRootComponent(CollisionComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(CollisionComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

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

	ProjectileAudioComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, CollisionComponent,
	                                                                FName("SocketName"));
	InitFX();

	SetLifeSpan(LifeTime);
}

void ASSProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
                                    AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                    const FHitResult& Hit)
{
	if (!GetWorld()) return;

	if (bHasHit) return;
	bHasHit = true;

	if (MovementComponent)
	{
		MovementComponent->StopMovementImmediately();
	}

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),
	                                    DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this,
	                                    GetController(), DoFullDamage);

	/*DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24,
		FColor::Yellow, false, 5.0f);*/
	WeaponFXComponent->PlayImpactFX(Hit);

	if (CollisionComponent)
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}

	if (MeshComponent)
	{
		MeshComponent->SetVisibility(false);
	}

	if (ProjectileAudioComponent)
	{
		ProjectileAudioComponent->Stop();
	}

	if (TraceFXComponent)
	{
		TraceFXComponent->Deactivate();
	}
}

AController* ASSProjectile::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());

	return Pawn ? Pawn->GetController() : nullptr;
}

void ASSProjectile::InitFX()
{
	if (!GetWorld()) return;

	TraceFXComponent = SpawnFX();

	if (TraceFXComponent)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_LifeSpanExpired);
		TraceFXComponent->OnSystemFinished.AddDynamic(this, &ASSProjectile::OnNiagaraFinished);

		TraceFXComponent->SetActive(true);
	}
}

UNiagaraComponent* ASSProjectile::SpawnFX() const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached
	(TraceFX, CollisionComponent, FName("SocketName"),
	 FVector::ZeroVector, FRotator::ZeroRotator,
	 EAttachLocation::SnapToTarget, true);
}

void ASSProjectile::OnNiagaraFinished(UNiagaraComponent* Component)
{
	Destroy();
}
