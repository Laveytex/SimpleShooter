// Simple Shooter Game.


#include "Player/SSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SSCharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
ASSBaseCharacter::ASSBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.0f, 100.0f,80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<USSHealthComponent>("HealthComponent");

	HealtnTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealtnTextComponent->SetupAttachment(RootComponent);
	HealtnTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USSWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ASSBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASSBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASSBaseCharacter::OnGroundLanded);

	
}

// Called every frame
void ASSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*//const auto Health = HealthComponent->GetHealth();
	//TakeDamage(0.1f, FDamageEvent{}, Controller, this);*/
}

// Called to bind functionality to input
void ASSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASSBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASSBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASSBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASSBaseCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASSBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASSBaseCharacter::OnStartRuning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASSBaseCharacter::OnEndRuning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USSWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USSWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USSWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USSWeaponComponent::Reload);
}

bool ASSBaseCharacter::IsRunning() const
{
	return IsMovingForwad && IsRun && !GetVelocity().IsZero();
}

float ASSBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASSBaseCharacter::SetPlayerColor(const FLinearColor& Color) const
{
	const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInst) return;

	MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

void ASSBaseCharacter::MoveForward(float Amount)
{
	IsMovingForwad = Amount > 0.0f;
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASSBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASSBaseCharacter::OnStartRuning()
{
	IsRun = true;
}

void ASSBaseCharacter::OnEndRuning()
{
	IsRun = false;
}

void ASSBaseCharacter::OnDeath()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Dead"));

	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.0f);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASSBaseCharacter::OnHealthChanged(const float Health,  float HealthDelta) const
{
	HealtnTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASSBaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	if(FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped
	(LandedDamageVelocity, LandedDamage, FallVelocityZ);

	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr); 
}
