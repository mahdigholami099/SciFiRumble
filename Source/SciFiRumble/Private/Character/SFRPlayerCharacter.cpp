// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRPlayerCharacter.h"

#include "Camera/SFRCameraActor.h"
#include "GameState/SFRMultiplayerGameState.h"
#include "Kismet/KismetMathLibrary.h"

FBarrelRotation ASFRPlayerCharacter::GetBarrelRotation()
{
	const float GunRotatorY = GetInputAxisValue(FName("GunRotatorY"));          
	const float GunRotatorX = GetInputAxisValue(FName("GunRotatorX"));
	UE_LOG(LogTemp, Warning, TEXT("X: %f         Y: %f"), GunRotatorX, GunRotatorY);
	const float GamepadRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector,
		FVector{
			-1 * GunRotatorY,
			GunRotatorX,
			0.0f}).Yaw;
	if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
	{
		if (const ASFRCameraActor* Camera = GameState->GetCamera())
		{
			const float ActorRotationRelativeToCamera = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), Camera->GetActorRotation()).Yaw;
			const float Result = GamepadRotation - ActorRotationRelativeToCamera;
			return Result < 0 ? Result + 360: Result;
		}
	}
	return GamepadRotation;
}

void ASFRPlayerCharacter::MoveForwardCallback(float AxisValue)
{
	AddMovementInput(CameraForwardVector, AxisValue);
}

void ASFRPlayerCharacter::MoveRightCallback(float AxisValue)
{
	AddMovementInput(CameraRightVector, AxisValue);
}

bool ASFRPlayerCharacter::CustomDestroy_Implementation()
{
	return Super::CustomDestroy_Implementation();
}

void ASFRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveY", this, &ASFRPlayerCharacter::MoveForwardCallback);
	InputComponent->BindAxis("MoveX", this, &ASFRPlayerCharacter::MoveRightCallback);
	InputComponent->BindAxis("GunRotatorY", this, &ASFRPlayerCharacter::Nothing);
	InputComponent->BindAxis("GunRotatorX", this, &ASFRPlayerCharacter::Nothing);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASFRPlayerCharacter::Fire);

}

void ASFRPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
	{
		if (IsValid(GameState->GetCamera()))
		{
			CameraForwardVector = GameState->GetCamera()->GetActorForwardVector();
			CameraRightVector = GameState->GetCamera()->GetActorRightVector();
		}
	}
}
