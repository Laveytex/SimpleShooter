// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSDevDamageActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API ASSDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxExtent;
};
