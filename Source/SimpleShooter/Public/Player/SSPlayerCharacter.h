// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSBaseCharacter.h"
#include "SSPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIMPLESHOOTER_API ASSPlayerCharacter : public ASSBaseCharacter
{
	GENERATED_BODY()

public:
	ASSPlayerCharacter(const FObjectInitializer& ObjInit);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual bool IsRunning() const override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	virtual void OnDeath() override;
	
private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnEndRunning();

	bool IsRun = false;
	bool IsMovingForward = false;
};
