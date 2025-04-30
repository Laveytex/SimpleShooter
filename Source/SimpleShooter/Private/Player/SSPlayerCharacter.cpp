// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SSPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASSPlayerCharacter::ASSPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.0f, 100.0f,80.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArm);
	CameraComponent->bUsePawnControlRotation = false;

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ASSPlayerCharacter::OnDeath()
{
	Super::OnDeath();
	
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASSPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASSPlayerCharacter::OnCameraCollisionEndOverlap);
	
}

void ASSPlayerCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASSPlayerCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASSPlayerCharacter::OnStartRunning()
{
	IsRun = true;
}

void ASSPlayerCharacter::OnEndRunning()
{
	IsRun = false;
}

void ASSPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASSPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASSPlayerCharacter::CheckCameraOverlap() const
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> AttachedChildren;
	GetMesh()->GetChildrenComponents(true, AttachedChildren);

	for (const auto MeshChild : AttachedChildren)
	{
		const auto MeshChildrenGeometry =   Cast<UPrimitiveComponent>(MeshChild);
		if (MeshChildrenGeometry)
		{
			MeshChildrenGeometry->SetOwnerNoSee(HideMesh);
		}
	}
}

void ASSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASSPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASSPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASSPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASSPlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASSPlayerCharacter::Jump);
	//PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASSPlayerCharacter::OnStartRunning);
	//PlayerInputComponent->BindAction("Run", IE_Released, this, &ASSPlayerCharacter::OnEndRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USSWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USSWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USSWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USSWeaponComponent::Reload);

	DECLARE_DELEGATE_OneParam(FZoomImputSignature, bool)
	PlayerInputComponent->BindAction<FZoomImputSignature>("Zoom", IE_Pressed, WeaponComponent, &USSWeaponComponent::Zoom, true);
	PlayerInputComponent->BindAction<FZoomImputSignature>("Zoom", IE_Released, WeaponComponent, &USSWeaponComponent::Zoom, false);
}

bool ASSPlayerCharacter::IsRunning() const
{
	return IsMovingForward && IsRun && !GetVelocity().IsZero();
}

