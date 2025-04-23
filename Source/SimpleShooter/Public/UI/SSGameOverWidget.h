// Fill out your copyright notice in the Description page of Project Settings.

	#pragma once

	#include "CoreMinimal.h"
	#include "Blueprint/UserWidget.h"
	#include "SSGameOverWidget.generated.h"


	enum class ESSMatchState : uint8;
	class UVerticalBox;
	/**
	 * 
	 */
	UCLASS()
	class SIMPLESHOOTER_API USSGameOverWidget : public UUserWidget
	{
		GENERATED_BODY()

	public:
		virtual bool Initialize() override;

	protected:
		UPROPERTY(meta = (BindWidget))
		UVerticalBox* PlayerStatBox;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	private:
		void OnMatchStateChange(ESSMatchState State);
		void UpdatePlayerStat() const;
	};
