// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/SSMenuWidget.h"

#include "SSGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/SSLevelItemWidget.h"
#include "Sound/SoundCue.h"

void USSMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USSMenuWidget::OnStartGame);
	}
	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USSMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

void USSMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (Animation != HideAnimation) return;

	if (!GetWorld()) return;

	const auto GameInstance = GetSSGameInstance();
	if (!GameInstance) return;

	UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void USSMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
	if(!GetWorld()) return;
	UGameplayStatics::PlaySound2D(this, ButtonStartSound);
}

void USSMenuWidget::OnQuitGame()
{
	if (!GetWorld()) return;
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USSMenuWidget::InitLevelItems()
{
	const auto GameInstance = GetSSGameInstance();
	if (!GameInstance) return;

	checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Level data must not be empty!"))

	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for (auto LevelData : GameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USSLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if (!LevelItemWidget) continue;
		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelection.AddUObject(this, &USSMenuWidget::OnLevelSelected);

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

void USSMenuWidget::OnLevelSelected(const FLevelData& Data)
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

USSGameInstance* USSMenuWidget::GetSSGameInstance() const
{
	if (!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<USSGameInstance>();
}
