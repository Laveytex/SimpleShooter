// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "SSWeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API USSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USSWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);
	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* Effect;
		
};