// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSGameOverWidget.h"

#include "SSGameModeBase.h"
#include "SSUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SSPlayerState.h"
#include "UI/SSPlayerStatRowsWidget.h"

void USSGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (GetWorld())
	{
		const auto GameMod = Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMod)
		{
			GameMod->OnMatchStateChanged.AddUObject(this, &USSGameOverWidget::OnMatchStateChange);
		}
	}

	if (ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USSGameOverWidget::OnResetLevel);
	}
}

void USSGameOverWidget::OnMatchStateChange(const ESSMatchState State)
{
	if (State == ESSMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}

void USSGameOverWidget::UpdatePlayerStat() const
{
	if (!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerStat = Cast<ASSPlayerState>(Controller->PlayerState);
		if (!PlayerStat) continue;

		//const auto PlayerStatWidget = CreateWidget<USSPlayerStatRowSWidget>(PlayerStatRowWidgetClass);
		const auto PlayerStatWidget = CreateWidget<USSPlayerStatRowsWidget>(GetWorld(), PlayerStatRowWidgetClass);

		if (!PlayerStatWidget) continue;

		PlayerStatWidget->SetPlayerName(FText::FromString(PlayerStat->GetPlayerName()));
		PlayerStatWidget->SetKills(SSUtils::TextFromInt(PlayerStat->GetKillsNum()));
		PlayerStatWidget->SetDeath(SSUtils::TextFromInt(PlayerStat->GetDeathsNum()));
		PlayerStatWidget->SetTeam(SSUtils::TextFromInt(PlayerStat->GetTeamID()));
		PlayerStatWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatWidget->SetTeamColor(PlayerStat->GetTeamColor());

		PlayerStatBox->AddChild(PlayerStatWidget);
	}
}

void USSGameOverWidget::OnResetLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
