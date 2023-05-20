// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SFRMultiplayerGameMode.generated.h"

class ASFRAICharacter;
USTRUCT()
struct FSpawnData
{
	GENERATED_BODY()

	UPROPERTY()
	APlayerController* Controller;

	UPROPERTY()
	ACharacter* Character;

	FSpawnData(APlayerController* Controller, ACharacter* Character): Controller(Controller), Character(Character)
	{}

	FSpawnData(APlayerController* Controller): Controller(Controller), Character(nullptr)
	{}

	FSpawnData(ACharacter* Character): Controller(nullptr), Character(Character)
	{}

	FSpawnData(): Controller(nullptr), Character(nullptr)
	{}

	bool operator==(const FSpawnData Other) const
	{
		return Other.Controller == Controller;
	}
};

UENUM(BlueprintType)
enum class EOrder : uint8
{
	Next,
	Before,
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnCharacter, int, CharacterIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReadySpawnCharacter, int, CharacterIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);

/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnSpawnCharacter OnSpawnCharacter;

	UPROPERTY(BlueprintAssignable)
	FOnReadySpawnCharacter OnReadySpawnCharacter;

	UPROPERTY(BlueprintAssignable)
	FOnConfirmCharacter OnConfirmCharacter;

	UPROPERTY(BlueprintAssignable)
	FOnGameStart OnGameStart;
	
protected:

	int MaxPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> CustomizeCharacterCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector SpawnLocationOffset;

	int NumberOfPlayerCharacterSpawned = 0;

	TArray<FSpawnData> SpawnData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ASFRAICharacter> AICharacter;

public:

	ASFRMultiplayerGameMode();

	UFUNCTION(BlueprintCallable)
	void SpawnNewCharacter(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void ChangeCharacter(const EOrder Order);

	UFUNCTION(BlueprintCallable)
	void ChangeSkin(const EOrder Order);

	UFUNCTION(BlueprintCallable)
	void ConfirmCharacter();

	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintCallable)
    void SpawnAI(APlayerController* PlayerController);
	
protected:

	virtual void BeginPlay() override;

	virtual void InitializeHUDForPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
};
