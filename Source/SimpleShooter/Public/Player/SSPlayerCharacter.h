// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SSBaseCharacter.h"
#include "SSPlayerCharacter.generated.h"

class USphereComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent;

	virtual void OnDeath() override;
	virtual void BeginPlay() override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void OnStartRunning();
	void OnEndRunning();
	void CheckCameraOverlap() const;

	bool IsRun = false;
	bool IsMovingForward = false;

	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OnComponentEndOverlap,
	                                 AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
