// Simple Shooter Game.


#include "UI/SSGameHUD.h"

#include "SSGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESSMatchState::InProgress,
		CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESSMatchState::Pause,
		CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

	for (const auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget  = GameWidgetPair.Value;
		if (!GameWidget) continue;
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if(GetWorld())
	{
		const auto GameMod =  Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());
		if(!GameMod) return;
		GameMod->OnMatchStateChanged.AddUObject(this, &AMyHUD::OnMatchStateChange);
	}
}

void AMyHUD::DrawCrossHair()
{
	const int32 SizeX = Canvas->SizeX;
	const int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5);

	constexpr float HalfLineSize = 10.0f;
	constexpr float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
 	
	DrawLine(Center.Min - HalfLineSize, Center.Max,
		Center.Min + HalfLineSize, Center.Max,
		LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize,
		Center.Min, Center.Max + HalfLineSize,
		LineColor, LineThickness);
}

void AMyHUD::OnMatchStateChange(const ESSMatchState State)
{
	if (CurrentGameWidget)
	{
		CurrentGameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameWidgets.Contains(State))
	{
		CurrentGameWidget = GameWidgets[State];
	}
	if (CurrentGameWidget)
	{
		CurrentGameWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
