// Simple Shooter Game.


#include "AI/SSBaseAICharacter.h"

#include "BrainComponent.h"
#include "AI/SSAIController.h"
#include "Components/SSAIWeaponComponent.h"
#include "Components/SSHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/SSHealthBarWidget.h"

ASSBaseAICharacter::ASSBaseAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USSAIWeaponComponent>("WeaponAIComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASSAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("health Widget");
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASSBaseAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateHealthWidgetVisibility();
}

void ASSBaseAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void ASSBaseAICharacter::OnDeath()
{
	const auto SSController = Cast<ASSAIController>(Controller);
	if (SSController && SSController->BrainComponent)
	{
		SSController->BrainComponent->Cleanup();
	}
	Super::OnDeath();
}

void ASSBaseAICharacter::OnHealthChanged(float Health, float HealthDelta) const
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthWidget = Cast<USSHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if(!HealthWidget) return;
	HealthWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASSBaseAICharacter::UpdateHealthWidgetVisibility() const
{
	if (!GetWorld() || !HealthWidgetComponent || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(GetActorLocation(), PlayerLocation);
	HealthWidgetComponent->SetVisibility(Distance <= HealthVisibilityDistance);
}