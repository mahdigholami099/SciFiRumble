// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SFRMultiplayerGameMode.h"

#include "Kismet/GameplayStatics.h"

void ASFRMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	uint8 CurrentPlayer = 1;
	while (IsValid(UGameplayStatics::CreatePlayer(GetWorld())) || CurrentPlayer <= MaxPlayer)
	{
		CurrentPlayer++;
	}
	
}
