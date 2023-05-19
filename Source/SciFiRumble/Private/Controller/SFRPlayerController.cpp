// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SFRPlayerController.h"

#include "Camera/SFRCameraActor.h"
#include "GameMode/SFRMultiplayerGameMode.h"
#include "GameState/SFRMultiplayerGameState.h"
#include "Kismet/GameplayStatics.h"


void ASFRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeNotCasted = UGameplayStatics::GetGameMode(GetWorld());
	if (!IsValid(GameModeNotCasted)) return;

	if (ASFRMultiplayerGameMode* GameMode = Cast<ASFRMultiplayerGameMode>(GameModeNotCasted))
	{
		GameMode->OnGameStart.AddDynamic(this, &ASFRPlayerController::GameStart);
	}
}

void ASFRPlayerController::GameStart()
{
	EnableInput(this);

	if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
	{
		if (IsValid(GameState->GetCamera()))
		{
			SetViewTarget(GameState->GetCamera());
		}
	}

}
