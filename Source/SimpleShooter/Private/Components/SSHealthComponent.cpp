// Simple Shooter Game.


#include "Components/SSHealthComponent.h"


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
	SetHealt(MaxHealth);
	
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USSHealthComponent::OnTakeAnyDamage);
	}
}

void USSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	HealTime = HealthDelay;
	
	SetHealt(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	OnHealthChanged.Broadcast(Health);
	
	//Health -= Damage;
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this,  &USSHealthComponent::HealUpdate, HealUpdateTime, true, HealthDelay);
	}
}

void USSHealthComponent::HealUpdate()
{
	SetHealt(Health + HealModifire);
	
	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USSHealthComponent::SetHealt(float NewHealh)
{
	Health = FMath::Clamp(NewHealh, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

bool USSHealthComponent::IsHealthFull() const
{
	return  FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USSHealthComponent::TryToAddHealth(int32 HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	
	SetHealt(Health + HealthAmount);
	
	return true; 
}
