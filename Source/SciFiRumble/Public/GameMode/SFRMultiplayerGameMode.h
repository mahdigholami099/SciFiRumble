// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SFRMultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SCIFIRUMBLE_API ASFRMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 MaxPlayer;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldFillWithAI = true;


protected:

	virtual void BeginPlay() override;
};
