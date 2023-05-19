// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SFRCharacter.h"
#include "SFRPlayerCharacter.generated.h"

class ASFRCameraActor;
/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRPlayerCharacter : public ASFRCharacter
{
	GENERATED_BODY()

public:

	FVector CameraForwardVector;

	FVector CameraRightVector;

	UPROPERTY()
	ASFRCameraActor* Camera;

public:

	virtual FBarrelRotation GetBarrelRotation() override;

	void MoveForwardCallback(float AxisValue);

	void MoveRightCallback(float AxisValue);

	void Nothing(float Nothing) {}

	virtual bool CustomDestroy_Implementation() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void GameStart();
	
};
