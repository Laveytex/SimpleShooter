// Simple Shooter Game.


#include "Components/SSCharacterMovementComponent.h"

#include "Player/SSBaseCharacter.h"

float USSCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASSBaseCharacter* Player = Cast<ASSBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning()  ? MaxSpeed * RunModifire: MaxSpeed;
}
