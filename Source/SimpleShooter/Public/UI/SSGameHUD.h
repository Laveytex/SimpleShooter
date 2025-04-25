// Simple Shooter Game.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSGameHUD.generated.h"

class USSBaseWidget;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<ESSMatchState, USSBaseWidget*> GameWidgets;

	UPROPERTY()
	USSBaseWidget* CurrentGameWidget = nullptr;

	void DrawCrossHair();
	void OnMatchStateChange(ESSMatchState State);
};
