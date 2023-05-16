// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/SFRMultiplayerGameState.h"

#include "Camera/SFRCameraActor.h"
#include "Kismet/GameplayStatics.h"

void ASFRMultiplayerGameState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASFRCameraActor::StaticClass(), Result);
	if (Result.Num() > 0)
	{
		Camera = Cast<ASFRCameraActor>(Result[0]);
	}
}
