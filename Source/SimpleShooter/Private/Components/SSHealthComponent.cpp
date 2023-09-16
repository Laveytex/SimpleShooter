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
	
	OnHealthChanged.Broadcast(Health, 0.0f);
	
	//Health -= Damage;
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this,  &USSHealthComponent::HealUpdate, HealUpdateTime, true, HealthDelay);
	}

	PlayCameraShake();
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
	const auto  NextHealth = FMath::Clamp(NewHealh, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USSHealthComponent::PlayCameraShake()
{
	if(IsDead()) return;
	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;
	//Controller->ClientStartCameraShake()
	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
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
