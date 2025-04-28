// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SSPlayerController.generated.h"

enum class ESSMatchState : uint8;
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

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void OnPauseGame();
	void OnMatchStateChange(ESSMatchState State);
	void OnMuteSound();
};
