// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSGameCreateWidget.h"

#include "SSGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/SSLevelItemWidget.h"
#include "Sound/SoundCue.h"

void USSGameCreateWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USSGameCreateWidget::OnStartGame);
	}

	InitLevelItems();
}

void USSGameCreateWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (Animation != HideAnimation) return;

	if (!GetWorld()) return;

	const auto GameInstance = GetSSGameInstance();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void USSGameCreateWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
	if(!GetWorld()) return;
	UGameplayStatics::PlaySound2D(this, ButtonStartSound);
}

void USSGameCreateWidget::InitLevelItems()
{
	const auto GameInstance = GetSSGameInstance();
	if (!GameInstance) return;

	checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Level data must not be empty!"))

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	if(!LevelItemWidgetClass) return;
	
	for (auto LevelData : GameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USSLevelItemWidget>(GetWorld(), LevelItemWidgetClass);

		if (!LevelItemWidget) continue;
		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelection.AddUObject(this, &USSGameCreateWidget::OnLevelSelected);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemsWidgets.Add(LevelItemWidget);
	}

	if (GameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(GameInstance->GetLevelsData().Top());
	}
	else
	{
		OnLevelSelected(GameInstance->GetStartupLevel());
	}
}

void USSGameCreateWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto GameInstance = GetSSGameInstance();
	if (!GameInstance) return;

	GameInstance->SetStartupLevel(Data);

	for (const auto LevelItemWidget : LevelItemsWidgets)
	{
		if (LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

USSGameInstance* USSGameCreateWidget::GetSSGameInstance() const
{
	if (!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<USSGameInstance>();
}
