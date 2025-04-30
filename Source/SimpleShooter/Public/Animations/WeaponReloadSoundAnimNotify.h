// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/SSAnimNotify.h"
#include "WeaponReloadSoundAnimNotify.generated.h"

UCLASS()
class SIMPLESHOOTER_API UWeaponReloadSoundAnimNotify : public USSAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* SoundToPlay;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
