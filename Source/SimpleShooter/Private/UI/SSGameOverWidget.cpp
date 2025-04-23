// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SSGameOverWidget.h"

#include "SSGameModeBase.h"
#include "SSUtils.h"
#include "Components/VerticalBox.h"
#include "Player/SSPlayerState.h"
#include "UI/SSPlayerStatRowSWidget.h"

bool USSGameOverWidget::Initialize()
{
	if (GetWorld())
	{
		const auto GameMod = Cast<ASSGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMod)
		{
			GameMod->OnMatchStateChanged.AddUObject(this, &USSGameOverWidget::OnMatchStateChange);
		}
	}

	return Super::Initialize();
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
		const auto PlayerStatWidget = CreateWidget<USSPlayerStatRowSWidget>(GetWorld(), PlayerStatRowWidgetClass);

		if (!PlayerStatWidget) continue;

		PlayerStatWidget->SetPlayerName(FText::FromString(PlayerStat->GetPlayerName()));
		PlayerStatWidget->SetKills(SSUtils::TextFromInt(PlayerStat->GetKillsNum()));
		PlayerStatWidget->SetDeath(SSUtils::TextFromInt(PlayerStat->GetDeathsNum()));
		PlayerStatWidget->SetTeam(SSUtils::TextFromInt(PlayerStat->GetTeamID()));
		PlayerStatWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatWidget);
	}
}
