// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSGameHUD.generated.h"

enum class ESSMatchState : uint8;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;
	
private:
	void DrawCrossHair();
	void OnMatchStateChange(ESSMatchState State);
};
