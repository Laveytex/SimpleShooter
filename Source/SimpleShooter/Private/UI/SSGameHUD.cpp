// Simple Shooter Game.


#include "UI/SSGameHUD.h"

#include "Engine/Canvas.h"

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AMyHUD::DrawCrossHair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;
	const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
 	
	DrawLine(Center.Min - HalfLineSize, Center.Max,
		Center.Min + HalfLineSize, Center.Max,
		LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize,
		Center.Min, Center.Max + HalfLineSize,
		LineColor, LineThickness);
}
