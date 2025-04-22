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
	}
}

void USSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

	// ?
	//HealTime = HealthDelay;
	
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
