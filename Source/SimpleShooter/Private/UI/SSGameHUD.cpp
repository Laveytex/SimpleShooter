// Simple Shooter Game.


#include "UI/SSGameHUD.h"

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
	
	const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
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
