// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SFRMultiplayerGameState.generated.h"


UENUM(BlueprintType)
enum class EGameStatus : uint8
{
	SpawnCharacter,
	CustomizeCharacter,
	InMiddleOfGame,
};

class ASFRCameraActor;
/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRMultiplayerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	EGameStatus GameStatus = EGameStatus::SpawnCharacter;
	
protected:
	
	UPROPERTY()
	ASFRCameraActor* Camera;

public:

	UFUNCTION(BlueprintCallable)
	ASFRCameraActor* GetCamera() const;
	
protected:

	virtual void BeginPlay() override;
};
