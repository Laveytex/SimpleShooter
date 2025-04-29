// Simple Shooter Game.


#include "Components/SSHealthComponent.h"
#include "SSGameModeBase.h"
#include "Perception/AISense_Damage.h"
#include "Player/SSBaseCharacter.h"

// Sets default values for this component's properties
USSHealthComponent::USSHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USSHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USSHealthComponent::OnTakeAnyDamage);
		ComponentOwner->OnTakePointDamage.AddDynamic(this, &USSHealthComponent::OnTakePointDamage);
		ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USSHealthComponent::OnTakeRadialDamage);
	}
}

void USSHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	
	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USSHealthComponent::SetHealth(float NewHealth)
{
	const auto  NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USSHealthComponent::PlayCameraShake() const
{
	if(IsDead()) return;
	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;
	//Controller->ClientStartCameraShake()
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USSHealthComponent::Killed(const AController* KillerController) const
{
	const auto GameMode = Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());
	if(!GameMode) return;
	const auto Player = Cast<APawn>(GetOwner());
	const auto VictimController = Player ? Player->Controller : nullptr;

	GameMode->Killed(KillerController, VictimController);
}

void USSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
										 AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Display, TEXT("OnAnyDamage %f"),Damage);
}

void USSHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
	FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
	const UDamageType* DamageType, AActor* DamageCauser)
{
	const auto FinalDamage = Damage * GetPointDamageModifire(DamagedActor, BoneName);
	UE_LOG(LogTemp, Display, TEXT("OnPointDamage %f, bome: %s"),FinalDamage, *BoneName.ToString() );
	ApplyDamage(FinalDamage, InstigatedBy);
}

void USSHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	FVector Origin, const FHitResult& HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Display, TEXT("OnRadialDamage %f"),Damage);
	ApplyDamage(Damage, InstigatedBy);
}

void USSHealthComponent::ApplyDamage(const float Damage, const AController* InstigatedBy)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	
	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	OnHealthChanged.Broadcast(Health, 0.0f);
	
	//Health -= Damage;
	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}	
	else if (AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this,  &USSHealthComponent::HealUpdate, HealUpdateTime, true, HealthDelay);
	}

	PlayCameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}

void USSHealthComponent::ReportDamageEvent(const float Damage, const AController* InstigatedController) const
{
	if (!GetWorld() || !GetOwner() || !InstigatedController || !InstigatedController->GetPawn()) return;

	UAISense_Damage::ReportDamageEvent(GetWorld(),
		GetOwner(),
		InstigatedController->GetPawn(),
		Damage,
		InstigatedController->GetPawn()->GetActorLocation(),
		GetOwner()->GetActorLocation());
}

float USSHealthComponent::GetPointDamageModifire(AActor* DamagedActor, const FName& BoneName)
{
	const auto Character = Cast<ACharacter>(DamagedActor);
	if(!Character || !Character->GetMesh() || !Character->GetMesh()->GetBodyInstance(BoneName)) return 1.0f;

	const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
	if(!DamageModifiers.Contains(PhysMaterial)) return 1.0f;

	return DamageModifiers[PhysMaterial];
}

bool USSHealthComponent::IsHealthFull() const
{
	return  FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USSHealthComponent::TryToAddHealth(const int32 HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	
	SetHealth(Health + HealthAmount);
	
	return true; 
}
