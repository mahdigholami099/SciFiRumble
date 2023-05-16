// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/SFRPlayerController.h"

#include "Camera/SFRCameraActor.h"
#include "GameState/SFRMultiplayerGameState.h"

void ASFRPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (const ASFRMultiplayerGameState* GameState = GetWorld()->GetGameState<ASFRMultiplayerGameState>())
	{
		if (GameState->GetCamera() != nullptr)
		{
			SetViewTarget(GameState->GetCamera());
		}
	}
}
