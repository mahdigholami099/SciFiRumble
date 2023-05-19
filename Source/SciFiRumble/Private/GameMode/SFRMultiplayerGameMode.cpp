// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SFRMultiplayerGameMode.h"

#include "Character/SFRCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "GameState/SFRMultiplayerGameState.h"
#include "Kismet/GameplayStatics.h"

ASFRMultiplayerGameMode::ASFRMultiplayerGameMode()
{
	bStartPlayersAsSpectators = true;
}

void ASFRMultiplayerGameMode::SpawnNewCharacter(APlayerController* PlayerController)
{
	// check if this controller already claimed some character
	if (SpawnData.Contains(PlayerController)) return;

	// check and change GameStatus
	if (ASFRMultiplayerGameState* GS = GetGameState<ASFRMultiplayerGameState>())
	{
		if (GS->GameStatus != EGameStatus::SpawnCharacter) return;
		GS->GameStatus = EGameStatus::CustomizeCharacter;
	}
	else return;

	// Broadcast new work to sync the ui or other actors
	OnSpawnCharacter.Broadcast(NumberOfPlayerCharacterSpawned);

	// disable other controller input for don't interrupt
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerActor = It->Get();
		if (PlayerController != PlayerActor)
		{
			DisableInput(PlayerActor);
		}
	}

	// spawn character and store it for possess and modify
	if (const AActor* PlayerStart = FindPlayerStart(PlayerController, FString::FromInt(NumberOfPlayerCharacterSpawned)))
	{
		FTransform Transform = PlayerStart->GetActorTransform();
		Transform.SetLocation(Transform.GetLocation() + SpawnLocationOffset);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (ACharacter* Character = GetWorld()->SpawnActor<ACharacter>(DefaultPawnClass, Transform, SpawnParameters))
		{
			SpawnData.Add({PlayerController, Character});
		}
	}
	
}

void ASFRMultiplayerGameMode::ChangeCharacter(const EOrder Order)
{
	// check GameStatus
	if (const ASFRMultiplayerGameState* GS = GetGameState<ASFRMultiplayerGameState>())
	{
		if (GS->GameStatus != EGameStatus::CustomizeCharacter) return;
	}
	else return;

	if (SpawnData.Num() == 0) return;

	if (ASFRCharacter* Character = Cast<ASFRCharacter>(SpawnData.Last().Character))
	{
		Character->ChangeCharacter(Order);
	}
}

void ASFRMultiplayerGameMode::ChangeSkin(const EOrder Order)
{
	// check GameStatus
	if (const ASFRMultiplayerGameState* GS = GetGameState<ASFRMultiplayerGameState>())
	{
		if (GS->GameStatus != EGameStatus::CustomizeCharacter) return;
	}
	else return;

	if (SpawnData.Num() == 0) return;

	if (ASFRCharacter* Character = Cast<ASFRCharacter>(SpawnData.Last().Character))
	{
		Character->ChangeSkin(Order);
	}
}

void ASFRMultiplayerGameMode::ConfirmCharacter()
{
	// check and change GameStatus
	if (ASFRMultiplayerGameState* GS = GetGameState<ASFRMultiplayerGameState>())
	{
		if (GS->GameStatus != EGameStatus::CustomizeCharacter) return;
		NumberOfPlayerCharacterSpawned++;
		// we can spawn other player or ai
		if (NumberOfPlayerCharacterSpawned < MaxPlayer)
		{
			GS->GameStatus = EGameStatus::SpawnCharacter;
		}
		// Game should start cause we reach maximum player for this map
		else
		{
			GS->GameStatus = EGameStatus::InMiddleOfGame;
			StartGame();
			return;
		}
	}
	else return;

	// enable all controller input
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PlayerActor = It->Get();
		EnableInput(PlayerActor);
	}
	
	OnReadySpawnCharacter.Broadcast(NumberOfPlayerCharacterSpawned);
	
}

void ASFRMultiplayerGameMode::StartGame()
{
	for (const FSpawnData EachSpawnDate: SpawnData)
	{
		EachSpawnDate.Controller->Possess(EachSpawnDate.Character);
	}
	OnGameStart.Broadcast();
}

void ASFRMultiplayerGameMode::FillRestWithAI()
{
	
	StartGame();
}

void ASFRMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);
	MaxPlayer = OutActors.Num();

	uint8 CurrentPlayer = 1;
	while (IsValid(UGameplayStatics::CreatePlayer(GetWorld())) || CurrentPlayer <= MaxPlayer)
	{
		CurrentPlayer++;
	}

	// set camera to CustomizeCharacterCamera
	OutActors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CustomizeCharacterCamera, OutActors);
	if (OutActors.IsValidIndex(0))
	{
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetViewTarget(OutActors[0]);
	}

	OnReadySpawnCharacter.Broadcast(NumberOfPlayerCharacterSpawned);
}

void ASFRMultiplayerGameMode::InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer)
{
	if (UGameplayStatics::GetPlayerControllerID(NewPlayer) == 0)
	{
		Super::InitializeHUDForPlayer_Implementation(NewPlayer);
	}
}

UClass* ASFRMultiplayerGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return nullptr;
}
