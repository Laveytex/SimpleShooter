// Simple Shooter Game.


#include "Weapon/Components/SSWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
USSWeaponFXComponent::USSWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}

void USSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

