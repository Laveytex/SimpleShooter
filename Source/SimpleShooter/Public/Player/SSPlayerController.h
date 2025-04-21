// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController.generated.h"

class USSRespawnComponent;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASSPlayerController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USSRespawnComponent* SSRespawnComponent;
};
