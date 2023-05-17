// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SFRMultiplayerGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void ASFRMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);
	const uint8 MaxPlayer = OutActors.Num();

	uint8 CurrentPlayer = 1;
	while (IsValid(UGameplayStatics::CreatePlayer(GetWorld())) || CurrentPlayer <= MaxPlayer)
	{
		CurrentPlayer++;
	}
	
}
