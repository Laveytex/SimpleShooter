// Simple Shooter Game.


#include "Weapon/Components/SSWeaponFXComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
USSWeaponFXComponent::USSWeaponFXComponent()
{

	PrimaryComponentTick.bCanEverTick = false;


}

void USSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	auto Effect = DefaultEffect;
	
	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (EffectsMap.Contains(PhysMat))
		{
			Effect = EffectsMap[PhysMat];
			
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s = StringVariable "), *Hit.PhysMaterial.Get()->GetName()));
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

