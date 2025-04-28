// Simple Shooter Game.


#include "Weapon/Components/SSWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
USSWeaponFXComponent::USSWeaponFXComponent(): DefaultImpactData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USSWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	if(!GetWorld()) return;
	
	auto ImpactData = DefaultImpactData;
	
	if (Hit.PhysMaterial.IsValid())
	{
		const auto PhysMat = Hit.PhysMaterial.Get();
		if (ImpactDataMap.Contains(PhysMat))
		{
			ImpactData = ImpactDataMap[PhysMat];
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s = StringVariable "), *Hit.PhysMaterial.Get()->GetName()));
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect,
		Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material,
		ImpactData.DecalData.Size,Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);
}

