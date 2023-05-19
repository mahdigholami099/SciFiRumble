// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SFRPlayerCharacter.h"

#include "Camera/SFRCameraActor.h"
#include "GameMode/SFRMultiplayerGameMode.h"
#include "GameState/SFRMultiplayerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

FBarrelRotation ASFRPlayerCharacter::GetBarrelRotation()
{
	const float GunRotatorY = GetInputAxisValue(FName("GunRotatorY"));          
	const float GunRotatorX = GetInputAxisValue(FName("GunRotatorX"));
	const float GamepadRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector,
		FVector{
			-1 * GunRotatorY,
			GunRotatorX,
			0.0f}).Yaw;
	if (!IsValid(Camera))
	{
		if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
		{
			Camera = GameState->GetCamera();
		}
	}
	if (!IsValid(Camera)) return GamepadRotation;
	const float ActorRotationRelativeToCamera = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), Camera->GetActorRotation()).Yaw;
	const float Result = GamepadRotation - ActorRotationRelativeToCamera;
	return Result < 0 ? Result + 360: Result;
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

	AGameModeBase* GameModeNotCasted = UGameplayStatics::GetGameMode(GetWorld());
	if (!IsValid(GameModeNotCasted)) return;

	if (ASFRMultiplayerGameMode* GameMode = Cast<ASFRMultiplayerGameMode>(GameModeNotCasted))
	{
		GameMode->OnGameStart.AddDynamic(this, &ASFRPlayerCharacter::GameStart);
	}
}

void ASFRPlayerCharacter::GameStart()
{
	if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
	{
		Camera = GameState->GetCamera();
		if (IsValid(Camera))
		{
			CameraForwardVector = Camera->GetActorForwardVector();
			CameraRightVector = Camera->GetActorRightVector();
		}
	}
}
